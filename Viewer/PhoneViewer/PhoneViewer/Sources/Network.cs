using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace PhoneViewer
{
    class SocketClient
    {
        Socket _socket;
        ManualResetEvent _sync;

        public SocketClient()
        {
            _sync = new ManualResetEvent(false);
        }

        public bool Connect(string host, int port)
        {
            DnsEndPoint hostEntry = new DnsEndPoint(host, port);

            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            SocketAsyncEventArgs socketEvents = new SocketAsyncEventArgs();
            socketEvents.RemoteEndPoint = hostEntry;

            socketEvents.Completed += new EventHandler<SocketAsyncEventArgs>(delegate(object o, SocketAsyncEventArgs e)
                {
                    _sync.Set();
                });
            _sync.Reset();

            _socket.ConnectAsync(socketEvents);

            _sync.WaitOne(1000);

            if (socketEvents.SocketError == SocketError.Success)
                return true;
            return false;
        }

        public void Send(string msg)
        {
            if (_socket != null)
            {
                SocketAsyncEventArgs socketEvent = new SocketAsyncEventArgs();
                socketEvent.RemoteEndPoint = _socket.RemoteEndPoint;
                socketEvent.Completed += new EventHandler<SocketAsyncEventArgs>(delegate(object o, SocketAsyncEventArgs e)
                    {
                        _sync.Set();
                    });
                byte[] tmp = Encoding.UTF8.GetBytes(msg);
                socketEvent.SetBuffer(tmp, 0, tmp.Length);

                _sync.Reset();

                if (_socket.SendAsync(socketEvent))
                    _sync.WaitOne(100);
            }
        }

        public string Receive()
        {
            string ret = String.Empty;
            if (_socket != null)
            {
                SocketAsyncEventArgs socketEvent = new SocketAsyncEventArgs();
                socketEvent.RemoteEndPoint = _socket.RemoteEndPoint;

                socketEvent.SetBuffer(new byte[4096], 0, 4096); 

                socketEvent.Completed += new EventHandler<SocketAsyncEventArgs>(delegate(object o, SocketAsyncEventArgs e)
                    {
                        _sync.Set();
                    });
                _sync.Reset();

                if (_socket.ReceiveAsync(socketEvent))
                    _sync.WaitOne(100);
                if (socketEvent.SocketError == SocketError.Success)
                {
                    ret = Encoding.UTF8.GetString(socketEvent.Buffer, socketEvent.Offset, socketEvent.BytesTransferred);
                }
            }
            return ret;
        }
    }

    class Network
    {
        SocketClient s;
        Treatment t;
        Queue<string> _in;
        string tmp;

        bool connected;

        public void Initialize(GamePage p)
        {
            Byte[] buff = new byte[128];
            _in = new Queue<string>();
            t = new Treatment();
            s = new SocketClient();

            t.Initialize(p);
            try
            {
                if (s.Connect(Infos.GetInstance().host, Int32.Parse(Infos.GetInstance().port)))
                {
                    connected = true;
                    if (s.Receive().CompareTo("BIENVENUE\n") == 0)
                    {
                        s.Send("GRAPHIC\n");
                    }
                }
                else
                {
                    connected = false;
                }
            }
            catch
            {
                connected = false;
            }
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
                _in = new Queue<string>(_in.Concat(res.ToList()));
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
