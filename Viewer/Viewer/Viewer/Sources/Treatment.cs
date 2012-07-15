﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;

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
            Vector2 dim = parent.Map.getSize();
            if (dim.X != int.Parse(a[0]) || dim.Y != int.Parse(a[1]))
            {
                parent.Map.resizeMap(int.Parse(a[0]), int.Parse(a[1]));
            }
        }

        private void bct(string[] a)
        {
            parent.Map.getCase(int.Parse(a[0]), int.Parse(a[1])).Inventory.setAll(uint.Parse(a[2]),
                uint.Parse(a[3]), uint.Parse(a[4]), uint.Parse(a[5]), uint.Parse(a[6]), uint.Parse(a[7]), uint.Parse(a[8]));
        }

        private void tna(string[] a)
        {
            parent.Teams.Add(a[0]);
        }

        private void pnw(string[] a)
        {
            parent.Players.Add(new Player(this.parent.Sprites, int.Parse(a[0]), int.Parse(a[1]), int.Parse(a[2]), Player.convertDir(int.Parse(a[3])), int.Parse(a[4]), a[5], this.parent.Teams.FindIndex(delegate(string n) { return n == a[5]; })));
            parent.Players[parent.Players.Count - 1].Inventory.nourriture = 10;
        }
        private void ppo(string[] a)
        {
            Player P;

            P = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            if (P != null)
            {
                P.setPos(int.Parse(a[1]), int.Parse(a[2])).Dir = Player.convertDir(int.Parse(a[3]));
                P.State = Player.States.IDLE;
                if (this.parent.Followed != null && this.parent.Followed.Id == P.Id)
                {
                    Rectangle r = new Rectangle();
                    r.X = -(-P.Pos.Y * (this.parent.Map.getSquare().Width / 2) + (P.getPos().X + 1) * (this.parent.Map.getSquare().Width / 2) + ((int)this.parent.Map.getSize().Y - 1) * (this.parent.Map.getSquare().Width / 2) - 550);
                    r.Y = -(P.Pos.Y * (this.parent.Map.getSquare().Height / 2) + (P.getPos().X) * (this.parent.Map.getSquare().Height / 2) - ((int)this.parent.Map.getSize().Y - 1) * (this.parent.Map.getSquare().Height / 2) - 340);
                    this.parent.Map.Square = r;
                }
                if (parent.Followed != null && P == parent.Followed)
                    this.parent.Sounds.PlaySound("ppo");
            }
        }

        private void plv(string[] a)
        {
            Player pl = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            pl.Level = int.Parse(a[1]);
            if (parent.Followed != null && pl != null && pl == parent.Followed)
                this.parent.Sounds.PlaySound("plv");
        }

        private void pin(string[] a)
        {
            Player pl = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            if (pl != null)
            {
                pl.setPos(int.Parse(a[1]), int.Parse(a[2]));
                pl.Inventory.nourriture = uint.Parse(a[3]);
                pl.Inventory.linemate = uint.Parse(a[4]);
                pl.Inventory.deraumere = uint.Parse(a[5]);
                pl.Inventory.sibur = uint.Parse(a[6]);
                pl.Inventory.mendiane = uint.Parse(a[7]);
                pl.Inventory.phiras = uint.Parse(a[8]);
                pl.Inventory.thystame = uint.Parse(a[9]);
            }
        }

        private void pex(string[] a)
        {
            Player P = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            if (P != null)
            {
                P.State = Player.States.EXPULSE;
                if (parent.Followed != null && P == parent.Followed)
                    this.parent.Sounds.PlaySound("pex");
            }
        }

        private void pbc(string[] a)
        {
            Player P = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            if (P != null)
            {
                string b = a.Skip(1).Aggregate(delegate(string one, string two) { return one + " " + two; });
                P.setBroadcast(b);
                parent.addBroadcast(P.Team, b);
                if (parent.Followed != null && P == parent.Followed)
                    this.parent.Sounds.PlaySound("pbc");
            }
        }

        private void pic(string[] a)
        {
            foreach (string s in a.Skip(3))
            {
                Player P = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(s); });
                if (P != null)
                {
                    P.State = Player.States.INCANT;
                    if (parent.Followed != null && P == parent.Followed)
                        this.parent.Sounds.PlaySound("pic");
                }
            }
        }

        private void pie(string[] a)
        {
            foreach (Player p in parent.Players.FindAll(delegate(Player p) { return p.getPos().X == int.Parse(a[0]) && p.getPos().Y == int.Parse(a[1]); }))
            {
                p.State = int.Parse(a[2]) == 0 ? Player.States.INCANT_FAIL : Player.States.INCANT_SUCCESS;
            }
        }
        private void pfk(string[] a)
        {
            Player P = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            if (P != null)
            {
                P.State = Player.States.FORK;
                if (parent.Followed != null && P == parent.Followed)
                    this.parent.Sounds.PlaySound("pfk");
            }
        }

        private void pdr(string[] a)
        {
            Player P = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            if (parent != null)
            {
                P.State = Player.States.DROP;
                if (parent.Followed != null && P == parent.Followed)
                    this.parent.Sounds.PlaySound("pdr");
            }
        }

        private void pgt(string[] a)
        {
            Player P = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            if (P != null)
            {
                P.State = Player.States.TAKE;
                if (parent.Followed != null && P == parent.Followed)
                    this.parent.Sounds.PlaySound("pgt");
            }
        }

        private void pdi(string[] a)
        {
            Player P = parent.Players.Find(delegate(Player p) { return p.Id == int.Parse(a[0]); });
            if (P != null)
            {
                P.State = Player.States.DEAD;
                if (parent.Followed != null && P == parent.Followed)
                    this.parent.Sounds.PlaySound("pdi");
            }
        }

        private void enw(string[] a)
        {
            parent.Eggs.Add(new Egg(this.parent.Sprites, int.Parse(a[0]), int.Parse(a[2]), int.Parse(a[3])));
        }

        private void eht(string[] a)
        {
            Egg P = parent.Eggs.Find(delegate(Egg e) { return e.Id == int.Parse(a[0]); });
            if (P != null)
            {
                P.State = Egg.States.BROKE;
            }
        }

        private void ebo(string[] a)
        {
            Egg P = parent.Eggs.Find(e => e.Id == int.Parse(a[0]));
            if (P != null)
            {
                P.State = Egg.States.BORN;
            }
        }

        private void edi(string[] a)
        {
            Egg P = parent.Eggs.Find(delegate(Egg e) { return e.Id == int.Parse(a[0]); });
            if (P != null)
            {
                P.State = Egg.States.DEAD;
            }
        }

        private void sgt(string[] a)
        {
            parent.Time = int.Parse(a[0]);
        }

        private void seg(string[] a)
        {
            parent.End = true;
            parent.Winner = a[0];
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