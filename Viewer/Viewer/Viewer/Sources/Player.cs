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
    enum Direction
    {
        NORTH,
        EAST,
        WEST,
        SOUTH,
        LAST
    }

    class Player
    {
        Vector2 pos;
        Sprite[] player;
        Direction dir;

        public Player()
        {
            this.pos = new Vector2(0, 0);
            this.dir = Direction.NORTH;
            this.player = new Sprite[4];
        }

        public void Load(ContentManager cm)
        {
            this.player[0] = new Sprite(cm.Load<Texture2D>("Players/player1"));
            this.player[1] = new Sprite(cm.Load<Texture2D>("Players/player2"));
            this.player[2] = new Sprite(cm.Load<Texture2D>("Players/player2"));
            this.player[3] = new Sprite(cm.Load<Texture2D>("Players/player2"));
        }

        public void Draw(GameTime gameTime, Rectangle square, SpriteBatch sb)
        {
            Point p;
            Point off;

            double factX = (48 * (square.Width / 155.0));
            double factY = (87 * (square.Height / 58.0));

            off.X = (int)(this.pos.X + 1) * (square.Width / 2);
            off.Y = (int)(this.pos.Y) * (square.Height / 2);

            p.X = (int)this.pos.Y  * (square.Width / 2) + (off.X) + square.X;
            p.Y = -(int)this.pos.Y * (square.Height / 2) + (off.Y) + square.Y;
            Rectangle tar = new Rectangle((int)(p.X + (int)(65 * (square.Width / 155.0))), (int)(p.Y - (int)(32 * (square.Height / 58.0))), (int)(factX), (int)(factY));
            this.player[(int)this.dir].Draw(sb, tar);
        }

        public Rectangle getBounds()
        {
            return this.player[0].getBounds();
        }
    }

}