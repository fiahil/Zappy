using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Viewer.Sources
{
    public partial class Popup : Form
    {
        bool validate;

        public Popup()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.validate = false;
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.validate = true;
            this.Close();
        }

        public string GetIp()
        {
            return this.textBox1.Text;
        }

        public Int32 GetPort()
        {
                return Int32.Parse(this.textBox2.Text);
        }

        public bool isValid()
        {
            return this.validate;
        }
    }
}
