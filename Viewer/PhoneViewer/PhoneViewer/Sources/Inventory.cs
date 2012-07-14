using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PhoneViewer
{
    public class Inventory
    {
        public uint nourriture;
        public uint linemate;
        public uint deraumere;
        public uint sibur;
        public uint mendiane;
        public uint phiras;
        public uint thystame;

        public Inventory()
        {
            this.nourriture = 0;
            this.linemate = 0;
            this.deraumere = 0;
            this.sibur = 0;
            this.mendiane = 0;
            this.phiras = 0;
            this.thystame = 0;
        }

        public void setAll(uint n, uint l, uint d, uint s, uint m, uint p, uint t)
        {
            this.nourriture = n;
            this.linemate = l;
            this.deraumere = d;
            this.sibur = s;
            this.mendiane = m;
            this.phiras = p;
            this.thystame = t;
        }
    }
}
