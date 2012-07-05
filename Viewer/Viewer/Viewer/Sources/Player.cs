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

namespace Viewer.Sources
{
    public enum Direction
    {
        NORTH,
        EAST,
        WEST,
        SOUTH,
        LAST
    }

    public class Player
    {
        public enum State
        {
            FORK,
            DEAD,
            TAKE,
            DROP,
            INCANT,
            EXPULSE,
            IDLE
        }

        Point pos;
        Sprite[] player;
        Sprite[] slvl;
        public Direction dir;
        public int lvl;
        public int id;
        public Inventory iv;
        public State st;
        string team;
        string broadcast;
        TimeSpan broacastTimer;
        Sprite[] sbroadcast;

        public Player(ContentManager cm, int idTeam)
        {
            this.pos = new Point(0, 0);
            this.dir = Direction.NORTH;
            this.player = new Sprite[4];
            this.slvl = new Sprite[7];
            this.sbroadcast = new Sprite[2];
            this.Load(cm, idTeam);
            this.lvl = 1;
            this.broadcast = null;
            this.broacastTimer = TimeSpan.Zero;
        }

        public Player(ContentManager cm, int x, int y, Direction dir, int lvl, string team, int idTeam)
        {
            this.pos = new Point(x, y);
            this.dir = Direction.EAST;
            this.player = new Sprite[4];
            this.slvl = new Sprite[7];
            this.sbroadcast = new Sprite[2];
            this.team = team;
            this.lvl = (lvl < 1 ? 1 : lvl);
            this.Load(cm, idTeam);
            this.broadcast = null;
            this.broacastTimer = TimeSpan.Zero;
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

        public void Load(ContentManager cm, int teamId)
        {
            if ((teamId % 2) == 0)
            {
                this.player[0] = new Sprite(cm.Load<Texture2D>("Players/BR"));
                this.player[1] = new Sprite(cm.Load<Texture2D>("Players/FR"));
                this.player[2] = new Sprite(cm.Load<Texture2D>("Players/FL"));
                this.player[3] = new Sprite(cm.Load<Texture2D>("Players/BL"));
            }
            else
            {
                this.player[0] = new Sprite(cm.Load<Texture2D>("Players/BR_2"));
                this.player[1] = new Sprite(cm.Load<Texture2D>("Players/FR_2"));
                this.player[2] = new Sprite(cm.Load<Texture2D>("Players/FL_2"));
                this.player[3] = new Sprite(cm.Load<Texture2D>("Players/BL_2"));
            }
            this.slvl[0] = new Sprite(cm.Load<Texture2D>("Level/level_1"));
            this.slvl[1] = new Sprite(cm.Load<Texture2D>("Level/level_2"));
            this.slvl[2] = new Sprite(cm.Load<Texture2D>("Level/level_3"));
            this.slvl[3] = new Sprite(cm.Load<Texture2D>("Level/level_4"));
            this.slvl[4] = new Sprite(cm.Load<Texture2D>("Level/level_5"));
            this.slvl[5] = new Sprite(cm.Load<Texture2D>("Level/level_6"));
            this.slvl[6] = new Sprite(cm.Load<Texture2D>("Level/level_7"));
            this.sbroadcast[0] = new Sprite(cm.Load<Texture2D>("Players/BroadcastL"));
            this.sbroadcast[1] = new Sprite(cm.Load<Texture2D>("Players/BroadcastR"));
        }

        public void Draw(GameTime gameTime, Rectangle square, Rectangle screen, SpriteBatch sb)
        {
            Point p;
            Point off;

            double factX = (this.player[(int)this.dir].getBounds().Width * (square.Width / 155.0));
            double factY = (this.player[(int)this.dir].getBounds().Height * (square.Height / 58.0));

            off.X = (this.pos.X + 1) * (square.Width / 2);
            off.Y = (this.pos.X) * (square.Height / 2);

            p.X = this.pos.Y * (square.Width / 2) + off.X + square.X;
            p.Y = -this.pos.Y * (square.Height / 2) + off.Y + square.Y;
            Rectangle tar = new Rectangle((int)(p.X + (int)(42 * (square.Width / 155.0))), (int)(p.Y - (int)(19 * (square.Height / 58.0))), (int)factX, (int)factY);
            if (screen.Intersects(tar))
            {
                this.player[(int)this.dir].Draw(sb, tar);
                factX = (this.slvl[this.lvl - 1].getBounds().Width * (square.Width / 155.0));
                factY = (this.slvl[this.lvl - 1].getBounds().Height * (square.Height / 58.0));
                if (this.dir == Direction.SOUTH || dir == Direction.WEST)
                    this.slvl[this.lvl - 1].Draw(sb, new Rectangle((int)(p.X + (int)(35 * (square.Width / 155.0))), (int)(p.Y - (int)(30 * (square.Height / 58.0))), (int)factX, (int)factY));
                else
                    this.slvl[this.lvl - 1].Draw(sb, new Rectangle((int)(p.X + (int)(48 * (square.Width / 155.0))), (int)(p.Y - (int)(30 * (square.Height / 58.0))), (int)factX, (int)factY));
                if (this.broadcast != null)
                {
                    this.broacastTimer = gameTime.TotalGameTime + TimeSpan.FromSeconds(2);
                    this.broadcast = null;
                }
                if (this.broacastTimer >= gameTime.TotalGameTime)
                {
                    factX = (this.sbroadcast[0].getBounds().Width * (square.Width / 155.0));
                    factY = (this.sbroadcast[0].getBounds().Height * (square.Height / 58.0));
                    if (this.dir == Direction.SOUTH || dir == Direction.WEST)
                        this.sbroadcast[0].Draw(sb, new Rectangle((int)(p.X + (int)(78 * (square.Width / 155.0))), (int)(p.Y - (int)(25 * (square.Height / 58.0))), (int)factX, (int)factY));
                    else
                        this.sbroadcast[1].Draw(sb, new Rectangle((int)(p.X + (int)(35 * (square.Width / 155.0))), (int)(p.Y - (int)(25 * (square.Height / 58.0))), (int)factX, (int)factY));

                }
            }
        }

        public Rectangle getBounds()
        {
            return this.player[(int)this.dir].getBounds();
        }
    }

}