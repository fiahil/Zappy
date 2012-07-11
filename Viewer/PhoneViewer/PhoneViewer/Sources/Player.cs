using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace PhoneViewer
{
    public enum Direction
    {
        NORTH,
        EAST,
        SOUTH,
        WEST,
        LAST
    }

    public class Player
    {
        public enum States
        {
            FORK,
            DEAD,
            FINISHED,
            TAKE,
            DROP,
            INCANT,
            INCANT_SUCCESS,
            INCANT_FAIL,
            EXPULSE,
            IDLE
        }

        Sprite[] player;
        Sprite[] stake;
        Sprite sincant;
        Sprite[] slvl;
        Sprite[] sfork;
        string broadcast;
        TimeSpan broacastTimer;
        Sprite[] sbroadcast;
        TimeSpan deadTimer;
        bool     dead;
        Sprite   sdead;

        Point pos;
        public Point Pos
        {
            get { return this.pos; } 
        }
        Direction dir;
        public Direction Dir
        {
            set { dir = value; }
        }

        int lvl;
        public int Level
        {
            get { return lvl; }
            set { lvl = value; }
        }

        int id;
        public int Id
        {
            get { return id; }
        }

        public Inventory iv; // TODO
        public Inventory Inventory
        {
            get { return iv; }
        }

        States st;
        public States State
        {
            get { return st; }
            set { st = value; }
        }

        string team;
        public string Team
        {
            get { return team; }
        }

        public Player(SpriteManager cm, int idTeam)
        {
            this.st = States.IDLE;
            this.pos = new Point(0, 0);
            this.dir = Direction.NORTH;
            this.player = new Sprite[4];
            this.stake = new Sprite[4];
            this.slvl = new Sprite[8];
            this.sfork = new Sprite[4];
            this.sbroadcast = new Sprite[2];
            this.Load(cm, idTeam);
            this.broadcast = null;
            this.broacastTimer = TimeSpan.Zero;
            this.deadTimer = TimeSpan.Zero;
            this.dead = false;
            this.lvl = 1;
            this.iv = new Inventory();
            this.team = "Poney";
        }

        public Player(SpriteManager cm, int id, int x, int y, Direction dir, int lvl, string team, int idTeam)
        {
            this.st = States.IDLE;
            this.id = id;
            this.pos = new Point(x, y);
            this.dir = dir;
            this.player = new Sprite[4];
            this.stake = new Sprite[4];
            this.slvl = new Sprite[8];
            this.sfork = new Sprite[4];
            this.sbroadcast = new Sprite[2];
            this.team = team;
            this.lvl = (lvl < 1 ? 1 : lvl);
            this.Load(cm, idTeam);
            this.deadTimer = TimeSpan.Zero;
            this.dead = false;
            this.broadcast = null;
            this.broacastTimer = TimeSpan.Zero;
            this.iv = new Inventory();
        }

        public Player setPos(int x, int y)
        {
            this.pos.X = x;
            this.pos.Y = y;
            return this;
        }

        public Point getPos()
        {
            return this.pos;
        }

        public void setBroadcast(string s)
        {
            this.broadcast = s;
        }

        static public Direction convertDir(int i)
        {
            if (i == 1)
            {
                return Direction.NORTH;
            }
            if (i == 2)
            {
                return Direction.EAST;
            }
            if (i == 3)
            {
                return Direction.SOUTH;
            }
            if (i == 4)
            {
                return Direction.WEST;
            }
            return Direction.LAST;
        }

        public void Load(SpriteManager sm, int teamId)
        {
            if ((teamId % 2) == 0)
            {
                this.player[0] = sm.GetSprite("Players/BR");
                this.player[1] = sm.GetSprite("Players/FR");
                this.player[2] = sm.GetSprite("Players/FL");
                this.player[3] = sm.GetSprite("Players/BL");
                this.stake[0] = sm.GetSprite("Players/BR_prend");
                this.stake[1] = sm.GetSprite("Players/FR_prend");
                this.stake[2] = sm.GetSprite("Players/FL_prend");
                this.stake[3] = sm.GetSprite("Players/BL_prend");
                this.sfork[0] = sm.GetSprite("Players/BR_fork");
                this.sfork[1] = sm.GetSprite("Players/FR_fork");
                this.sfork[2] = sm.GetSprite("Players/FL_fork");
                this.sfork[3] = sm.GetSprite("Players/BL_fork");
                this.sincant = sm.GetSprite("Players/incant");
            }
            else
            {
                this.player[0] = sm.GetSprite("Players/BR_2");
                this.player[1] = sm.GetSprite("Players/FR_2");
                this.player[2] = sm.GetSprite("Players/FL_2");
                this.player[3] = sm.GetSprite("Players/BL_2");
                this.stake[0] = sm.GetSprite("Players/BR_prend_2");
                this.stake[1] = sm.GetSprite("Players/FR_prend_2");
                this.stake[2] = sm.GetSprite("Players/FL_prend_2");
                this.stake[3] = sm.GetSprite("Players/BL_prend_2");
                this.sfork[0] = sm.GetSprite("Players/BR_fork_2");
                this.sfork[1] = sm.GetSprite("Players/FR_fork_2");
                this.sfork[2] = sm.GetSprite("Players/FL_fork_2");
                this.sfork[3] = sm.GetSprite("Players/BL_fork_2");
                this.sincant = sm.GetSprite("Players/incant_2");
            }
            this.slvl[0] = sm.GetSprite("Level/level_1");
            this.slvl[1] = sm.GetSprite("Level/level_2");
            this.slvl[2] = sm.GetSprite("Level/level_3");
            this.slvl[3] = sm.GetSprite("Level/level_4");
            this.slvl[4] = sm.GetSprite("Level/level_5");
            this.slvl[5] = sm.GetSprite("Level/level_6");
            this.slvl[6] = sm.GetSprite("Level/level_7");
            this.slvl[7] = sm.GetSprite("Level/level_8");
            this.sdead = sm.GetSprite("Players/dead");
            this.sbroadcast[0] = sm.GetSprite("Players/BroadcastL");
            this.sbroadcast[1] = sm.GetSprite("Players/BroadcastR");
        }

        public void Draw(GameTimerEventArgs gameTime, Rectangle square, Rectangle screen, SpriteBatch sb, Map map)
        {
            Point p;
            Point off;

            if (this.st == States.DEAD && this.dead == false)
            {
                this.deadTimer = gameTime.TotalTime + TimeSpan.FromSeconds(5);
                this.dead = true;
            }
            if (this.st == States.DEAD || this.st == States.FINISHED)
            {
                if (this.deadTimer >= gameTime.TotalTime)
                {
                    double factX = (this.sdead.getBounds().Width * (square.Width / 155.0));
                    double factY = (this.sdead.getBounds().Height * (square.Height / 58.0));

                    off.X = (this.pos.X + 1) * (square.Width / 2);
                    off.Y = (this.pos.X) * (square.Height / 2);

                    p.X = -this.pos.Y * (square.Width / 2) + off.X + square.X + ((int)map.getSize().Y - 1) * (square.Width / 2);
                    p.Y = this.pos.Y * (square.Height / 2) + off.Y + square.Y - ((int)map.getSize().Y - 1) * (square.Height / 2);
                    Rectangle tar = new Rectangle((int)(p.X + (int)(42 * (square.Width / 155.0))), (int)(p.Y - (int)(19 * (square.Height / 58.0))), (int)factX, (int)factY);
                    if (screen.Intersects(tar))
                        this.sdead.Draw(sb, tar);
                }
                else
                    this.st = States.FINISHED;
            }
            else
            {    
                Rectangle tar = Rectangle.Empty;
                double factX = 0.0;
                double factY = 0.0;

                if (this.st == States.TAKE || this.st == States.DROP)
                {
                    factX = (this.stake[(int)this.dir].getBounds().Width * (square.Width / 155.0));
                    factY = (this.stake[(int)this.dir].getBounds().Height * (square.Height / 58.0));

                    off.X = (this.pos.X + 1) * (square.Width / 2);
                    off.Y = (this.pos.X) * (square.Height / 2);

                    p.X = -this.pos.Y * (square.Width / 2) + off.X + square.X + ((int)map.getSize().Y - 1) * (square.Width / 2);
                    p.Y = this.pos.Y * (square.Height / 2) + off.Y + square.Y - ((int)map.getSize().Y - 1) * (square.Height / 2);
                    tar = new Rectangle((int)(p.X + (int)(42 * (square.Width / 155.0))), (int)(p.Y - (int)(19 * (square.Height / 58.0))), (int)factX, (int)factY);
                    if (screen.Intersects(tar))
                        this.stake[(int)this.dir].Draw(sb, tar);
                }
                else if (this.st == States.INCANT)
                {
                    factX = (this.sincant.getBounds().Width * (square.Width / 155.0));
                    factY = (this.sincant.getBounds().Height * (square.Height / 58.0));

                    off.X = (this.pos.X + 1) * (square.Width / 2);
                    off.Y = (this.pos.X) * (square.Height / 2);

                    p.X = -this.pos.Y * (square.Width / 2) + off.X + square.X + ((int)map.getSize().Y - 1) * (square.Width / 2);
                    p.Y = this.pos.Y * (square.Height / 2) + off.Y + square.Y - ((int)map.getSize().Y - 1) * (square.Height / 2);
                    tar = new Rectangle((int)(p.X + (int)(42 * (square.Width / 155.0))), (int)(p.Y - (int)(19 * (square.Height / 58.0))), (int)factX, (int)factY);
                    if (screen.Intersects(tar))
                        this.sincant.Draw(sb, tar);
                }
                else if (this.st == States.FORK)
                {
                    factX = (this.sfork[(int)this.dir].getBounds().Width * (square.Width / 155.0));
                    factY = (this.sfork[(int)this.dir].getBounds().Height * (square.Height / 58.0));

                    off.X = (this.pos.X + 1) * (square.Width / 2);
                    off.Y = (this.pos.X) * (square.Height / 2);

                    p.X = -this.pos.Y * (square.Width / 2) + off.X + square.X + ((int)map.getSize().Y - 1) * (square.Width / 2);
                    p.Y = this.pos.Y * (square.Height / 2) + off.Y + square.Y - ((int)map.getSize().Y - 1) * (square.Height / 2);
                    tar = new Rectangle((int)(p.X + (int)(42 * (square.Width / 155.0))), (int)(p.Y - (int)(19 * (square.Height / 58.0))), (int)factX, (int)factY);
                    if (screen.Intersects(tar))
                        this.sfork[(int)this.dir].Draw(sb, tar);
                }
                else if (this.st == States.INCANT)
                {
                    factX = (this.sincant.getBounds().Width * (square.Width / 155.0));
                    factY = (this.sincant.getBounds().Height * (square.Height / 58.0));

                    off.X = (this.pos.X + 1) * (square.Width / 2);
                    off.Y = (this.pos.X) * (square.Height / 2);

                    p.X = this.pos.Y * (square.Width / 2) + off.X + square.X;
                    p.Y = -this.pos.Y * (square.Height / 2) + off.Y + square.Y;
                    tar = new Rectangle((int)(p.X + (int)(42 * (square.Width / 155.0))), (int)(p.Y - (int)(19 * (square.Height / 58.0))), (int)factX, (int)factY);
                    if (screen.Intersects(tar))
                        this.sincant.Draw(sb, tar);
                }
                else
                {
                    factX = (this.player[(int)this.dir].getBounds().Width * (square.Width / 155.0));
                    factY = (this.player[(int)this.dir].getBounds().Height * (square.Height / 58.0));

                    off.X = (this.pos.X + 1) * (square.Width / 2);
                    off.Y = (this.pos.X) * (square.Height / 2);

                    p.X = -this.pos.Y * (square.Width / 2) + off.X + square.X + ((int)map.getSize().Y - 1)* (square.Width / 2);
                    p.Y = this.pos.Y * (square.Height / 2) + off.Y + square.Y - ((int)map.getSize().Y - 1) * (square.Height / 2);
                    tar = new Rectangle((int)(p.X + (int)(42 * (square.Width / 155.0))), (int)(p.Y - (int)(19 * (square.Height / 58.0))), (int)factX, (int)factY);
                    if (screen.Intersects(tar))
                        this.player[(int)this.dir].Draw(sb, tar);
                }
                if (screen.Intersects(tar))
                {
                    factX = (this.slvl[this.lvl - 1].getBounds().Width * (square.Width / 155.0));
                    factY = (this.slvl[this.lvl - 1].getBounds().Height * (square.Height / 58.0));
                    if (this.dir == Direction.NORTH || dir == Direction.WEST)
                        this.slvl[this.lvl - 1].Draw(sb, new Rectangle((int)(p.X + (int)(35 * (square.Width / 155.0))), (int)(p.Y - (int)(30 * (square.Height / 58.0))), (int)factX, (int)factY));
                    else
                        this.slvl[this.lvl - 1].Draw(sb, new Rectangle((int)(p.X + (int)(48 * (square.Width / 155.0))), (int)(p.Y - (int)(30 * (square.Height / 58.0))), (int)factX, (int)factY));
                    if (this.broadcast != null)
                    {
                        this.broacastTimer = gameTime.TotalTime + TimeSpan.FromSeconds(2);
                        this.broadcast = null;
                    }
                    if (this.broacastTimer >= gameTime.TotalTime)
                    {
                        factX = (this.sbroadcast[0].getBounds().Width * (square.Width / 155.0));
                        factY = (this.sbroadcast[0].getBounds().Height * (square.Height / 58.0));
                        if (this.dir == Direction.NORTH || dir == Direction.WEST)
                            this.sbroadcast[0].Draw(sb, new Rectangle((int)(p.X + (int)(78 * (square.Width / 155.0))), (int)(p.Y - (int)(25 * (square.Height / 58.0))), (int)factX, (int)factY));
                        else
                            this.sbroadcast[1].Draw(sb, new Rectangle((int)(p.X + (int)(35 * (square.Width / 155.0))), (int)(p.Y - (int)(25 * (square.Height / 58.0))), (int)factX, (int)factY));

                    }
                }
            }
        }

        public Rectangle getBounds()
        {
            return this.player[(int)this.dir].getBounds();
        }
    }

}