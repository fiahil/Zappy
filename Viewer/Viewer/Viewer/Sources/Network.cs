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
    class PopUp
    {
        Form menu;
        Button accept;
        Button cancel;
        Label ipLabel;
        Label portLabel;
        TextBox ip;
        TextBox port;
        public bool isValid;

        private void OnAccept(object sender, System.EventArgs e)
        {
            isValid = true;
            menu.Close();
        }

        private void OnCancel(object sender, System.EventArgs e)
        {
            isValid = false;
            menu.Close();
        }

        public string GetIp()
        {
            return ip.Text;
        }

        public Int32 GetPort()
        {
            try
            {
                return Int32.Parse(port.Text);
            }
            catch
            {
                return 0;
            }
        }

        public void Initialize()
        {
            menu = new Form();
            accept = new Button();
            cancel = new Button();
            ipLabel = new Label();
            portLabel = new Label();
            ip = new TextBox();
            port = new TextBox();

            accept.Text = "Ok";
            accept.Location = new Point(0, 50);
            accept.Click += OnAccept;

            cancel.Text = "Cancel";
            cancel.Location = new Point(100, 50);
            cancel.Click += OnCancel;
            

            ipLabel.Text = "Ip";

            portLabel.Text = "Port";
            portLabel.Location = new Point(125, 0);

            ip.Location = new Point(0, 20);
            port.Location = new Point(125, 20);


            menu.Text = "Infos Server";
            menu.Height = 100;
            menu.FormBorderStyle = FormBorderStyle.FixedDialog;
            menu.Controls.Add(accept);
            menu.Controls.Add(cancel);
            menu.Controls.Add(ip);
            menu.Controls.Add(port);
            menu.Controls.Add(ipLabel);
            menu.Controls.Add(portLabel);
            menu.ShowDialog();
        }
    }

    class Network
    {
        Socket s;
        Queue<string> _out;
        Queue<string> _in;
        string tmp;

        public void Initialize()
        {
            PopUp pop = new PopUp();
            Byte[] buff = new byte[128];
            _out = new Queue<string>();
            _in = new Queue<string>();

            pop.Initialize();
            if (pop.isValid)
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
                if (s.Poll(100, SelectMode.SelectRead))
                {
                    s.Receive(buff);
                }
                if (Encoding.UTF8.GetString(buff) == "BIENVENUE\n")
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
                    res = res.Reverse().Skip(1).Reverse() as string[];
                }
                _in.Concat(res);
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
