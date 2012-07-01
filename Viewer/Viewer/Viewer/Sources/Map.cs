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
    /// <summary>
    /// Elt class representing an square of the map
    /// </summary>
    class Elt
    {
        SpriteBatch sb;
        Inventory iv { get; set; }
        Sprite tile;

        public Rectangle Bounds;

        public Elt(SpriteBatch sb)
        {
            this.sb = sb;
        }

        public void Load(ContentManager cm)
        {
            this.tile = new Sprite(cm.Load<Texture2D>("tiles/base"), 1);
            this.Bounds = tile.getBounds();
        }

        public void Draw(Rectangle square)
        {
            this.tile.Draw(sb, square);
        }
    }

    /// <summary>
    /// Map class representing the whole terrain with cristals (Elt matrix)
    /// </summary>
    class Map : Microsoft.Xna.Framework.DrawableGameComponent
    {
        Vector2 dim;
        Rectangle square;
        Elt[,] map;
        bool[] edge;
        SpriteBatch sb;
        TimeSpan repeat;
        TimeSpan Vrep;
        TimeSpan Hrep;
        uint view;

        public Map(Game game, uint size_x, uint size_y)
            : base(game)
        {
            this.dim = new Vector2(size_x, size_y);
            this.map = new Elt[size_x, size_y];
            this.edge = new bool[4];

            this.square = new Rectangle();
            this.square.Height = 58;
            this.square.Width = 155;
            this.square.X = -(this.square.Width * (int)this.dim.X) / 4;
            this.square.Y = (this.square.Height * (int)this.dim.Y) / 4;

            this.repeat = TimeSpan.Zero;
            this.Hrep = TimeSpan.Zero;
            this.Vrep = TimeSpan.Zero;

            this.edge[0] = false;
            this.edge[1] = false;
            this.edge[2] = false;
            this.edge[3] = false;

            this.view = 0;
        }

        public void Load(ContentManager cm, SpriteBatch sb)
        {
            this.sb = sb;

            for (int i = 0; i < this.dim.X; ++i)
                for (int j = 0; j < this.dim.Y; ++j)
                {
                    this.map[i, j] = new Elt(sb);
                    this.map[i, j].Load(cm);
                }
        }

        public override void Initialize()
        {
            base.Initialize();
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            if (Keyboard.GetState().IsKeyDown(Keys.Z) && this.square.Height < 100 && this.repeat <= gameTime.TotalGameTime)
            {
                this.square.Height += 10;
                this.square.Width += 10;
                this.square.X -= 80;
                this.repeat = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);
            }
            if (Keyboard.GetState().IsKeyDown(Keys.X) && this.square.Height > 40 && this.repeat <= gameTime.TotalGameTime)
            {
                this.square.Height -= 10;
                this.square.Width -= 10;
                this.square.X += 80;
                this.repeat = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);

                if (this.view <= 50)
                {
                    this.square.Height += 10;
                    this.square.Width += 10;
                    this.square.X -= 80;
                }
            }
            if ((Keyboard.GetState().IsKeyDown(Keys.W) || Keyboard.GetState().IsKeyDown(Keys.Up)) && (this.view > 50 || edge[1]) && this.Vrep <= gameTime.TotalGameTime)
            {
                this.square.Y += 20;
                this.Vrep = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);
                this.edge[1] = false;
                this.edge[2] = true;
            }
            if ((Keyboard.GetState().IsKeyDown(Keys.S) || Keyboard.GetState().IsKeyDown(Keys.Down)) && (this.view > 50 || edge[2]) && this.Vrep <= gameTime.TotalGameTime)
            {
                this.square.Y -= 20;
                this.Vrep = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);
                this.edge[1] = true;
                this.edge[2] = false;
            }
            if ((Keyboard.GetState().IsKeyDown(Keys.A) || Keyboard.GetState().IsKeyDown(Keys.Left)) && (this.view > 50 || this.edge[0]) && this.Hrep <= gameTime.TotalGameTime)
            {
                this.square.X += 20;
                this.Hrep = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);
                this.edge[3] = true;
                this.edge[0] = false;
            }
            if ((Keyboard.GetState().IsKeyDown(Keys.D) || Keyboard.GetState().IsKeyDown(Keys.Right)) && (this.view > 50 || this.edge[3]) && this.Hrep <= gameTime.TotalGameTime)
            {
                this.square.X -= 20;
                this.Hrep = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);
                this.edge[3] = false;
                this.edge[0] = true;
            }
        }

        public override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);

            this.sb.Begin(SpriteSortMode.Deferred, BlendState.AlphaBlend);

            Point p = new Point(0, 0);
            Point off = new Point(0, 0);

            this.view = 0;

            for (int i = 0; i < this.dim.X; ++i, off.X += this.square.Width / 2, off.Y += this.square.Height / 2)
                for (int j = 0; j < this.dim.Y; ++j)
                {
                    p.X = j * (this.square.Width / 2) + (off.X) + this.square.X;
                    p.Y = -j * (this.square.Height /2) + (off.Y) + this.square.Y;

                    Rectangle target = new Rectangle(p.X, p.Y, this.square.Width, this.square.Height);

                    if (this.Game.Window.ClientBounds.Contains(target))
                        this.view += 1;

                    this.map[i, j].Draw(target);
                }

            this.sb.End();
        }
    }
}
