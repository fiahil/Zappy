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

        public Player(ContentManager cm)
        {

            this.pos = new Point(0, 0);
            this.dir = Direction.NORTH;
            this.player = new Sprite[4];
            this.slvl = new Sprite[7];
            this.Load(cm);
            this.lvl = 7;
        }

        public Player(ContentManager cm, int x, int y, Direction dir, int lvl, string team)
        {
            this.pos = new Point(x, y);
            this.dir = Direction.EAST;
            this.player = new Sprite[4];
            this.team = team;
            this.lvl = lvl;
            this.Load(cm);
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

        public void Load(ContentManager cm)
        {
            this.player[0] = new Sprite(cm.Load<Texture2D>("Players/BR"));
            this.player[1] = new Sprite(cm.Load<Texture2D>("Players/FR"));
            this.player[2] = new Sprite(cm.Load<Texture2D>("Players/FL"));
            this.player[3] = new Sprite(cm.Load<Texture2D>("Players/BL"));
            this.slvl[0] = new Sprite(cm.Load<Texture2D>("Level/level_1"));
            this.slvl[1] = new Sprite(cm.Load<Texture2D>("Level/level_2"));
            this.slvl[2] = new Sprite(cm.Load<Texture2D>("Level/level_3"));
            this.slvl[3] = new Sprite(cm.Load<Texture2D>("Level/level_4"));
            this.slvl[4] = new Sprite(cm.Load<Texture2D>("Level/level_5"));
            this.slvl[5] = new Sprite(cm.Load<Texture2D>("Level/level_6"));
            this.slvl[6] = new Sprite(cm.Load<Texture2D>("Level/level_7"));
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
                this.slvl[this.lvl - 1].Draw(sb, new Rectangle((int)(p.X + (int)(48 * (square.Width / 155.0))), (int)(p.Y - (int)(30 * (square.Height / 58.0))), (int)factX, (int)factY));
            }
        }

        public Rectangle getBounds()
        {
            return this.player[(int)this.dir].getBounds();
        }
    }

}