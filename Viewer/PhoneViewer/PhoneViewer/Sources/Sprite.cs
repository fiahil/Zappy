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
    public class Sprite
    {
        Texture2D texture;

        public Sprite(Texture2D t)
        {
            this.texture = t;
        }

        public void Draw(SpriteBatch sb, Rectangle square)
        {
            sb.Draw(this.texture, square, this.texture.Bounds, Color.White);
        }

        public Rectangle getBounds()
        {
            return this.texture.Bounds;
        }
    }
}
