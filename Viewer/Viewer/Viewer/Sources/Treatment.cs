using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Viewer.Sources
{

    delegate void TreatCmd(string[] a);
    class Treatment
    {
        Dictionary<string, TreatCmd> tab;
        Main parent;

        public void Initialize(Main p)
        {
            parent = p;
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
                try
                {
                    tab[cmd.Substring(0, 3)](cmd.Substring(4).Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries));
                }
                catch
                {
                }
            }
        }

        private void msz(string[] a)
        {
            Vector2 dim = parent.getMap().getSize();
            if (dim.X != int.Parse(a[0]) && dim.Y != int.Parse(a[1]))
            {
                parent.getMap().resizeMap(int.Parse(a[0]), int.Parse(a[1]));
            }
        }

        private void bct(string[] a)
        {
            parent.getMap().getCase(int.Parse(a[0]), int.Parse(a[1])).Iv.setAll(uint.Parse(a[2]),
                                                                           uint.Parse(a[3]),
                                                                           uint.Parse(a[4]),
                                                                           uint.Parse(a[5]),
                                                                           uint.Parse(a[5]),
                                                                           uint.Parse(a[6]),
                                                                           uint.Parse(a[7]));
        }

        private void tna(string[] a)
        {
            parent.tlist.Add(a[0]);
        }

        private void pnw(string[] a)
        {
            parent.getPlayers().Add(new Player(int.Parse(a[0]), int.Parse(a[1]), Player.convertDir(int.Parse(a[2])), int.Parse(a[3]), a[4]));
        }
        private void ppo(string[] a)
        {
            parent.getPlayers().Find(delegate(Player p) { return p.id == int.Parse(a[0]); })
                .setPos(int.Parse(a[1]), int.Parse(a[2])).dir = Player.convertDir(int.Parse(a[3]));
        }

        private void plv(string[] a)
        {
            parent.getPlayers().Find(delegate(Player p) { return p.id == int.Parse(a[0]); })
                .lvl = int.Parse(a[1]);
        }

        private void pin(string[] a)
        {
            Player pl = parent.getPlayers().Find(delegate(Player p) { return p.id == int.Parse(a[0]); });
            pl.setPos(int.Parse(a[1]), int.Parse(a[2]));
            pl.iv.nourriture    = uint.Parse(a[3]);
            pl.iv.linemate      = uint.Parse(a[4]);
            pl.iv.deraumere     = uint.Parse(a[5]);
            pl.iv.sibur         = uint.Parse(a[6]);
            pl.iv.mendiane      = uint.Parse(a[7]);
            pl.iv.phiras        = uint.Parse(a[8]);
            pl.iv.thystame      = uint.Parse(a[9]);
        }

        private void pex(string[] a)
        {
        }

        private void pbc(string[] a)
        {
        }
        private void pic(string[] a)
        {
        }
        private void pie(string[] a)
        {
        }
        private void pfk(string[] a)
        {
        }
        private void pdr(string[] a)
        {
        }
        private void pgt(string[] a)
        {
        }
        private void pdi(string[] a)
        {
        }
        private void enw(string[] a)
        {
        }
        private void eht(string[] a)
        {
        }
        private void ebo(string[] a)
        {
        }
        private void edi(string[] a)
        {
        }
        private void sgt(string[] a)
        {
        }
        private void seg(string[] a)
        {
        }
        private void smg(string[] a)
        {
        }
        private void suc(string[] a)
        {
        }
        private void sbp(string[] a)
        {
        }
    }
}
