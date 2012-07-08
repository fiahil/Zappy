using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace Viewer.Sources
{
    public class Egg
    {
        public enum States
        {
            BROKE,
            BORN,
            DEAD,
            IDLE
        }
        
        Point pos;
        Sprite egg;
        States st;
        int id;

        public int Id
        {
            get { return id; }
        }

        public States State
        {
            get { return st; }
            set { st = value; }
        }

        public Egg(SpriteManager cm,int id, int x, int y)
        {
            pos = new Point(x, y);
            this.id = id;
            this.egg = cm.GetSprite("Players/Egg");
        }

        public void Draw(GameTime gameTime, Rectangle square, Rectangle screen, SpriteBatch sb)
        {
            Point p;
            Point off;

            double factX = ((this.egg.getBounds().Width * 0.45) * (square.Width / 155.0));
            double factY = ((this.egg.getBounds().Height * 0.45) * (square.Height / 58.0));

            off.X = (this.pos.X + 1) * (square.Width / 2);
            off.Y = (this.pos.X) * (square.Height / 2);

            p.X = this.pos.Y * (square.Width / 2) + off.X + square.X;
            p.Y = -this.pos.Y * (square.Height / 2) + off.Y + square.Y;

            Rectangle tar = new Rectangle((int)(p.X + (int)(117 * (square.Width / 155.0))), (int)(p.Y + (int)(38 * (square.Height / 58.0))), (int)factX, (int)factY);
            if (screen.Intersects(tar))
                this.egg.Draw(sb, tar);
        }
    }
}
