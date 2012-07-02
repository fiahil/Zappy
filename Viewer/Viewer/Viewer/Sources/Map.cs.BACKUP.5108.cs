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
    /// Map class representing the whole terrain with cristals (Elt matrix)
    /// </summary>
    class Map : Microsoft.Xna.Framework.DrawableGameComponent
    {
        Vector2 dim;
        Rectangle square;
        Rectangle screen;
        Elt[,] map;
        bool[] edge;
        SpriteBatch sb;
        TimeSpan repeat;
        TimeSpan Vrep;
        TimeSpan Hrep;
        uint view;

        Sprite square_details;
        bool square_details_on;
        Point square_details_pos;
        TimeSpan square_setails_timer;
        Sprite[] _wall;
        Point[] clouds;

        SpriteFont sf;

        public Map(Game game, uint size_x, uint size_y)
            : base(game)
        {
            this.dim = new Vector2(size_x, size_y);
            this.map = new Elt[size_x, size_y];
            this.edge = new bool[4];
            this._wall = new Sprite[4];
            this.clouds = new Point[5];

            this.clouds[0] = new Point(300, 100);
            this.clouds[1] = new Point(600, 350);
            this.clouds[2] = new Point(900, 50);
            this.clouds[3] = new Point(1200, 300);
            this.clouds[4] = new Point(0, 250);


            this.screen = new Rectangle(0, 0, 1280, 720);
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
            this.square_details_pos = Point.Zero;
            this.square_details_on = false;
            this.square_setails_timer = TimeSpan.Zero;
        }

<<<<<<< HEAD
        //TODO REMOVE THIS
        static Random p = new Random();
=======
        public Rectangle getSquare()
        {
            return this.square;
        }
>>>>>>> a1d0f7ca82a048bf960251e7e5fb4485773f9dbd

        public void Load(ContentManager cm, SpriteBatch sb)
        {
            this.sb = sb;

            this.square_details = new Sprite(cm.Load<Texture2D>("Tiles/map_resources"));
            this.sf = cm.Load<SpriteFont>("Font/Classic");
            this._wall[0] = new Sprite(cm.Load<Texture2D>("Background/wall"));
            this._wall[1] = new Sprite(cm.Load<Texture2D>("Background/wall2"));
            this._wall[2] = new Sprite(cm.Load<Texture2D>("Background/wall3"));
            this._wall[3] = new Sprite(cm.Load<Texture2D>("Background/cloud"));

            for (int i = 0; i < this.dim.X; ++i)
                for (int j = 0; j < this.dim.Y; ++j)
                {
                    this.map[i, j] = new Elt(sb, new Point(i, j));
                    this.map[i, j].Load(cm);
                }
<<<<<<< HEAD

            //TODO REMOVE THIS
            foreach (Elt element in this.map)
            {
                if (p.Next(3) == 0)
                    element.Iv.setAll((uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10));
            }
=======
            this.map[0,0].iv.setAll(4,4,6,6,6,6,6);
>>>>>>> a1d0f7ca82a048bf960251e7e5fb4485773f9dbd
        }

        public override void Initialize()
        {
            base.Initialize();
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            for (int i = 0; i < 5; ++i)
            {
                if (this.clouds[i].X >= 1300)
                    this.clouds[i].X = -400;
                else
                    this.clouds[i].X += 1;
            }

            if (Keyboard.GetState().IsKeyDown(Keys.Z) && this.square.Height < 60 && this.repeat <= gameTime.TotalGameTime)
            {
                this.square.Height += 1;
                this.square.Width += 4;
                this.square.X -= (int)this.dim.X  * 2;
                this.repeat = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);
            }
            if (Keyboard.GetState().IsKeyDown(Keys.X) && this.square.Height > 40 && this.repeat <= gameTime.TotalGameTime)
            {
                this.square.Height -= 1;
                this.square.Width -= 4;
                this.square.X += (int)this.dim.X * 2;
                this.repeat = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);
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

            if (Mouse.GetState().LeftButton == ButtonState.Pressed)
            {
                for (int i = 0; i < this.dim.X; ++i)
                {
                    for (int j = 0; j < this.dim.Y; ++j)
                    {
                        if (this.map[i, j].isInPolygon(new Vector2(Mouse.GetState().X, Mouse.GetState().Y), this.square))
                        {
                            this.square_details_on = true;
                            this.square_setails_timer = gameTime.TotalGameTime + TimeSpan.FromSeconds(5);
                            this.map[this.square_details_pos.X, this.square_details_pos.Y].selected = false;
                            this.map[j, i].selected = true;
                            this.square_details_pos = new Point(j, i);
                        }
                    }
                }
            }

            if (this.square_setails_timer <= gameTime.TotalGameTime)
            {
                this.map[this.square_details_pos.X, this.square_details_pos.Y].selected = false;
                this.square_details_on = false;
            }
        }

        public override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);

            this.sb.Begin(SpriteSortMode.Deferred, BlendState.AlphaBlend);

            Rectangle tarcloud = new Rectangle(this.clouds[0].X, this.clouds[0].Y, 400, 200);
            this._wall[3].Draw(this.sb, tarcloud);
            tarcloud = new Rectangle(this.clouds[1].X, this.clouds[1].Y, 300, 150);
            this._wall[3].Draw(this.sb, tarcloud);
            tarcloud = new Rectangle(this.clouds[2].X, this.clouds[2].Y, 380, 190);
            this._wall[3].Draw(this.sb, tarcloud);
            tarcloud = new Rectangle(this.clouds[3].X, this.clouds[3].Y, 400, 200);
            this._wall[3].Draw(this.sb, tarcloud);
            tarcloud = new Rectangle(this.clouds[4].X, this.clouds[4].Y, 380, 190);
            this._wall[3].Draw(this.sb, tarcloud);
            
            Point p = new Point(0, 0);
            Point off = new Point(0, 0);

            string[] inventory = null;

            double factX = (200 * (this.square.Width / 155.0));
            double factY = (160 * (this.square.Height / 58.0));

            this.view = 0;
            int j = 0;

            for (int i = 0; i < this.dim.X + 1; ++i, off.X += this.square.Width / 2, off.Y += this.square.Height / 2)
            {
                for (j = (int)this.dim.Y - 1; j >= 0; --j)
                {
                    p.X = j * (this.square.Width / 2) + (off.X) + this.square.X;
                    p.Y = -j * (this.square.Height / 2) + (off.Y) + this.square.Y;

                    if (i != 0)
                    {
                        Rectangle target = new Rectangle(p.X, p.Y, this.square.Width, this.square.Height);

                        if (this.Game.Window.ClientBounds.Contains(target))
                            this.view += 1;

                        if (this.screen.Intersects(target))
                            this.map[i - 1, j].Draw(target);

                        if (this.map[i - 1, j].selected)
                        {
                            inventory = new string[7];
                            inventory[0] = this.map[i - 1, j].Iv.nourriture.ToString();
                            inventory[1] = this.map[i - 1, j].Iv.linemate.ToString();
                            inventory[2] = this.map[i - 1, j].Iv.deraumere.ToString();
                            inventory[3] = this.map[i - 1, j].Iv.sibur.ToString();
                            inventory[4] = this.map[i - 1, j].Iv.mendiane.ToString();
                            inventory[5] = this.map[i - 1, j].Iv.phiras.ToString();
                            inventory[6] = this.map[i - 1, j].Iv.thystame.ToString();
                        }
                    }

                    if (i == 1)
                    {
                        p.X = j * (this.square.Width / 2) + this.square.X;
                        p.Y = -j * (this.square.Height / 2) + this.square.Y;
<<<<<<< HEAD
                        Rectangle tar = new Rectangle((int)(p.X - (int)(31 * (this.square.Width / 155.0))), (int)(p.Y - (int)(101 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                        if (this.screen.Intersects(tar))
                            this._wall[2].Draw(this.sb, tar);
=======
                        Rectangle tar = new Rectangle((int)(p.X - (int)(33 * (this.square.Width / 155.0))), (int)(p.Y - (int)(103 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                        this._wall[2].Draw(this.sb, tar);
>>>>>>> a1d0f7ca82a048bf960251e7e5fb4485773f9dbd
                    }
                }
                if (i != 0)
                {
                    p.X = ((int)this.dim.Y - 1 - j) * (this.square.Width / 2) + (off.X) + this.square.X;
                    p.Y = - ((int)this.dim.Y - 1 - j) * (this.square.Height / 2) + (off.Y) + this.square.Y;
                    Rectangle tar2 = new Rectangle((int)(p.X - (int)(31 * (this.square.Width / 155.0))), (int)(p.Y - (int)(101 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                    if (this.screen.Intersects(tar2))
                        this._wall[i % 2].Draw(this.sb, tar2);
                }
            }
            if (this.square_details_on)
            {
                System.Diagnostics.Debug.Assert(inventory != null);
                this.square_details.Draw(this.sb, new Rectangle(this.Game.Window.ClientBounds.Width - this.square_details.getBounds().Width, 0, this.square_details.getBounds().Width, this.square_details.getBounds().Height));
                this.sb.DrawString(this.sf, inventory[0], new Vector2(1200, 100), Color.Black);
                this.sb.DrawString(this.sf, inventory[1], new Vector2(1200, 155), Color.Black);
                this.sb.DrawString(this.sf, inventory[2], new Vector2(1200, 210), Color.Black);
                this.sb.DrawString(this.sf, inventory[3], new Vector2(1200, 265), Color.Black);
                this.sb.DrawString(this.sf, inventory[4], new Vector2(1200, 325), Color.Black);
                this.sb.DrawString(this.sf, inventory[5], new Vector2(1200, 380), Color.Black);
                this.sb.DrawString(this.sf, inventory[6], new Vector2(1200, 440), Color.Black);
            }

            this.sb.End();
        }
    }
}
