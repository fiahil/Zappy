using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PhoneViewer
{

    class Network
    {
        Socket s;
        Treatment t;
        Queue<string> _out;
        Queue<string> _in;
        string tmp;

        bool connected;

        public void Initialize(GamePage p)
        {
            Byte[] buff = new byte[128];
            _out = new Queue<string>();
            _in = new Queue<string>();
            t = new Treatment();

            t.Initialize(p);
            if (true)
            {
               
            }
            else
            {
                connected = true;
            }
        }

        public void Update()
        {
            
            if (s!= null)
            {
                Byte[] buff = new byte[0];

                string[] res = (tmp).Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);
                if (buff[buff.Length - 1] != '\n')
                {
                    tmp = res[res.Length - 1];
                    res = res.Take(res.Length - 1).ToArray();
                }
                else
                {
                    tmp = "";
                }
                _in = new Queue<string>(_in.Concat(res.ToList()));
            }
            if (s != null && !s.Connected)
            {
                this.connected = false;
                return;
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
                _out.Enqueue(msg);

            }
        }
    }
}
