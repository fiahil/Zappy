using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Viewer.Sources
{

    private delegate void TreatCmd(string a);
    class Treatment
    {
        Dictionary<string, TreatCmd> tab;
        Map map;

        public void Initialize(Map m)
        {
            map = m;
            tab["msz"] = msz;
        }

        public void Treat(string cmd)
        {
            if (tab.ContainsKey(cmd.Substring(0, 3)))
            {
                tab[cmd.Substring(0, 3)](cmd.Substring(4));
            }
        }

        private void msz(string a)
        {

        }
    }
}
