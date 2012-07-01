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
    class Sprite
    {
        Texture2D texture;
        int currentFrame;
        int totalFrames;
        Rectangle frameSize;

        public Sprite(Texture2D t, int tf)
        {
            this.texture = t;
            this.currentFrame = 0;
            this.totalFrames = tf;
            this.frameSize = this.texture.Bounds;
            this.frameSize.Width /= this.totalFrames;
        }

        public void Next(int f = 1)
        {
            this.currentFrame += f;
            this.currentFrame %= this.totalFrames;
        }

        public void Reset()
        {
            this.currentFrame = 0;
        }

        public void Draw(SpriteBatch sb, Rectangle square)
        {
            Rectangle frame = this.frameSize;

            frame.X += this.frameSize.Width * this.currentFrame;
            frame.X %= this.texture.Bounds.Width;

            sb.Draw(this.texture, square, frame, Color.White);
        }

        public Rectangle getBounds()
        {
            return this.texture.Bounds;
        }
    }
}
