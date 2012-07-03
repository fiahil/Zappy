using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace Viewer.Sources
{

    class Network
    {
        Socket s;
        Treatment t;
        Queue<string> _out;
        Queue<string> _in;
        string tmp;

        public void Initialize(Main p)
        {
            Popup pop = new Popup();
            Byte[] buff = new byte[128];
            _out = new Queue<string>();
            _in = new Queue<string>();
            t = new Treatment();

            t.Initialize(p);
            pop.ShowDialog();
            if (pop.isValid())
            {
                IPAddress[] IPs = Dns.GetHostAddresses(pop.GetIp());

                s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                try
                {
                    s.Connect(IPs[0], pop.GetPort());
                }
                catch (SocketException e)
                {
                    Console.WriteLine("Error on Socket\nWhat: {0}", e.Message);
                }
                catch (NotSupportedException e)
                { // Format port invalid
                }

                if (s.Poll(-1, SelectMode.SelectRead))
                {
                    s.Receive(buff);
                }
                if (Encoding.UTF8.GetString(buff).CompareTo("BIENVENUE\n") == 0)
                {
                    s.Send(Encoding.UTF8.GetBytes("GRAPHIC\n"));
                }
            }
        }

        public void Update()
        {
            if (s!= null && s.Available > 0)
            {
                Byte[] buff = new byte[s.Available];
                s.Receive(buff);

                string[] res = (tmp + Encoding.UTF8.GetString(buff)).Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);
                if (buff[buff.Length - 1] != '\n')
                {
                    tmp = res[res.Length - 1];
                    res = res.Take(res.Length - 1).ToArray();
                }
                _in = new Queue<string>(_in.Concat(res.ToList()));
            }
            while (_in.Count > 0)
            {
                t.Treat(_in.Dequeue());
            }
        }

        public void SendDatas(string msg)
        {
            if (s != null)
            {
                _out.Enqueue(msg);
                while (s.Poll(-1, SelectMode.SelectWrite) && _out.Count > 0)
                {
                    s.Send(Encoding.UTF8.GetBytes(_out.Dequeue()));
                }
            }
        }
    }
}
