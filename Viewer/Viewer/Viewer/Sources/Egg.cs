using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Viewer.Sources
{
    public class Egg
    {
        public enum State
        {
            BROKE,
            BORN,
            DEAD,
            IDLE
        }
        
        Point pos;
        Sprite[] egg;
        public State st;
        public int id;

        public Egg(int id, int x, int y)
        {
            pos = new Point(x, y);
            this.id = id;
        }
    }
}
