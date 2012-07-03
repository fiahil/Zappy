using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Viewer.Sources
{
    public class Egg
    {
        Point pos;
        Sprite[] player;

        public Egg(int x, int y)
        {
            pos = new Point(x, y);
        }
    }
}
