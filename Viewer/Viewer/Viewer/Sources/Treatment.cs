using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Viewer.Sources
{

    delegate void TreatCmd(string a);
    class Treatment
    {
        Dictionary<string, TreatCmd> tab;
        Map map;

        public void Initialize(Map m)
        {
            map = m;
            tab = new Dictionary<string, TreatCmd>();
            tab["msz"] = msz;
            tab["bct"] = bct;
            tab["tna"] = tna;
            tab["pnw"] = pnw;
            tab["ppo"] = ppo;
            tab["plv"] = plv;
            tab["pin"] = pin;
            tab["pex"] = pex;
            tab["pbc"] = pbc;
            tab["pic"] = pic;
            tab["pie"] = pie;
            tab["pfk"] = pfk;
            tab["pdr"] = pdr;
            tab["pgt"] = pgt;
            tab["pdi"] = pdi;
            tab["enw"] = enw;
            tab["eht"] = eht;
            tab["ebo"] = ebo;
            tab["edi"] = edi;
            tab["sgt"] = sgt;
            tab["seg"] = seg;
            tab["smg"] = smg;
            tab["suc"] = suc;
            tab["sbp"] = sbp;
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
        private void bct(string a)
        {
        }
        private void tna(string a)
        {
        }
        private void pnw(string a)
        {
        }
        private void ppo(string a)
        {
        }
        private void plv(string a)
        {
        }
        private void pin(string a)
        {
        }
        private void pex(string a)
        {
        }
        private void pbc(string a)
        {
        }
        private void pic(string a)
        {
        }
        private void pie(string a)
        {
        }
        private void pfk(string a)
        {
        }
        private void pdr(string a)
        {
        }
        private void pgt(string a)
        {
        }
        private void pdi(string a)
        {
        }
        private void enw(string a)
        {
        }
        private void eht(string a)
        {
        }
        private void ebo(string a)
        {
        }
        private void edi(string a)
        {
        }
        private void sgt(string a)
        {
        }
        private void seg(string a)
        {
        }
        private void smg(string a)
        {
        }
        private void suc(string a)
        {
        }
        private void sbp(string a)
        {
        }
    }
}
