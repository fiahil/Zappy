using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace PhoneViewer
{
    public class SocketClient
    {
        Socket _socket;
        bool isConnected;

        Queue<string> _in;
        bool isReceiving;
        SocketAsyncEventArgs recvEvents;
        
        Queue<string> _out;
        bool isSending;
        SocketAsyncEventArgs sendEvents;

        public SocketClient()
        {
            isConnected = false;
            isReceiving = false;
            isSending = false;

            _in = new Queue<string>();
            _out = new Queue<string>();

            recvEvents = new SocketAsyncEventArgs();
            recvEvents.UserToken = this;
            recvEvents.Completed += ProcessRecv;
            recvEvents.SetBuffer(new byte[4096], 0, 4096);

            sendEvents = new SocketAsyncEventArgs();
            sendEvents.UserToken = this;
            sendEvents.Completed += ProcessSend;
        }

        static void ProcessRecv(object o, SocketAsyncEventArgs e)
        {
            SocketClient _this = e.UserToken as SocketClient;

            _this._in.Enqueue(Encoding.UTF8.GetString(e.Buffer, 0, e.Buffer.Length));
            _this.isReceiving = false;
        }

        static void ProcessSend(object o, SocketAsyncEventArgs e)
        {
            SocketClient _this = e.UserToken as SocketClient;

            if (_this._out.Count > 0)
            {
                byte[] s = Encoding.UTF8.GetBytes(_this._out.Dequeue());
                e.SetBuffer(s, 0, s.Length);
                while (!_this._socket.SendAsync(e))
                {
                    if (_this._out.Count == 0)
                    {
                        _this.isSending = false;
                        return;
                    }
                    s = Encoding.UTF8.GetBytes(_this._out.Dequeue());
                }
                return;
            }
            _this.isSending = false;
        }

        public bool Connect(string hostname, int port)
        {
            DnsEndPoint host = null;
            try
            {
                host = new DnsEndPoint(hostname, port);
            }
            catch
            {
                return false;
            }
            
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            ManualResetEvent sync = new ManualResetEvent(false);

            SocketAsyncEventArgs co = new SocketAsyncEventArgs();
            co.Completed += new EventHandler<SocketAsyncEventArgs>(delegate(object o, SocketAsyncEventArgs e)
                {
                    sync.Set();
                    if (e.SocketError == SocketError.Success)
                        isConnected = true;
                });

            co.RemoteEndPoint = host;
            recvEvents.RemoteEndPoint = host;
            sendEvents.RemoteEndPoint = host;

            sync.Reset();
            if (_socket.ConnectAsync(co))
                sync.WaitOne(10000);
            else
            {
                sync.Set();
            }
            return isConnected;
        }

        public string Receive()
        {
            string ret = String.Empty;

            if (!isReceiving)
            {
                isReceiving = true;
                _socket.ReceiveAsync(recvEvents);
            }
            if (_in.Count > 0)
            {
                ret = _in.Aggregate((a, b) => a + b);
                _in.Clear();
            }
            return ret;
        }

        public void Send(string msg)
        {
            if (_socket != null)
            {
                _out.Enqueue(msg);
                if (!isSending)
                {
                    byte[] s = Encoding.UTF8.GetBytes(_out.Dequeue());
                    sendEvents.SetBuffer(s, 0, s.Length);
                    _socket.SendAsync(sendEvents);
                }
            }
        }
    }

    public class Network
    {
        SocketClient s;
        Treatment t;
        Queue<string> _in;
        string tmp;

        bool connected;

        public SocketClient Socket
        {
            get { return s; }
        }

        public void Initialize(GamePage p)
        {
            t = new Treatment();
            s = new SocketClient();
            _in = new Queue<string>();

            t.Initialize(p);
            s.Connect(Infos.GetInstance().host, Int32.Parse(Infos.GetInstance().port));
        }

        public void Update()
        {
            
            if (s!= null)
            {
                string buff = s.Receive();

                string[] res = (tmp + buff).Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);
                if (buff.Length > 1 && buff[buff.Length - 1] != '\n')
                {
                    tmp = res[res.Length - 1];
                    res = res.Take(res.Length - 1).ToArray();
                }
                else
                {
                    tmp = String.Empty;
                }
                _in = new Queue<string>(_in.Concat(res));
            }

            while (_in.Count > 0)
            {
                t.Treat(_in.Dequeue());
            }
        }

        public bool IsConnected()
        {
            return connected;
        }

        public void SendDatas(string msg)
        {
            if (s != null)
            {
                s.Send(msg);
            }
        }
    }
}
