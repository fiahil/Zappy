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
        UP,
        DOWN,
        LEFT,
        RIGHT,
        LAST
    }

    class Player
    {
        Vector2 pos;
        Sprite player;
        Direction dir;

        public Player()
        {
        }
    }
}
