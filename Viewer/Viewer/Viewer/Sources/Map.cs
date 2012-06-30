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
    class Elt
    {
        uint x { get; set; }
        uint y { get; set; }
        Inventory iv { get; set; }
        List<Player> player { get; set; }
    }

    class Map : Microsoft.Xna.Framework.DrawableGameComponent
    {
        Elt[,] map;

        /// <summary>
        /// Ctor
        /// </summary>
        public Map(Game game, uint size_x, uint size_y)
            : base(game)
        {
            this.map = new Elt[size_x, size_y];
        }

        public override void Initialize()
        {
            base.Initialize();
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);
        }
    }
}
