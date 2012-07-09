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
    public class Map : Microsoft.Xna.Framework.DrawableGameComponent
    {
        Vector2 dim;
        Rectangle square;
        Rectangle screen;
        Elt[,] map;
        bool[] edge;
        SpriteBatch sb;
        TimeSpan Vrep;
        TimeSpan Hrep;
        uint view;

        Point square_details_pos;
        TimeSpan square_setails_timer;
        Sprite[] _wall;
        Point[] clouds;

        string[] inventory;
        public string[] Inventory
        {
            get { return inventory; }
        }

        bool square_details_on;
        public bool SquareDetailsOn
        {
            get { return square_details_on; }
        }

        Sprite square_details;
        public Sprite SquareDetails
        {
            get { return square_details; }
        }

        SpriteFont sf;

        public Map(Game game)
            : base(game)
        {
            this.dim = Vector2.Zero;
            this.map = null;
            this.edge = new bool[4];
            this._wall = new Sprite[9];
            this.clouds = new Point[5];

            this.clouds[0] = new Point(300, 100);
            this.clouds[1] = new Point(600, 350);
            this.clouds[2] = new Point(900, 50);
            this.clouds[3] = new Point(1200, 300);
            this.clouds[4] = new Point(0, 250);

            this.screen = new Rectangle(0, 0, 1280, 720);
            this.square = Rectangle.Empty;

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

        //TODO REMOVE THIS
        static Random p = new Random();

        public void resizeMap(int size_x, int size_y)
        {
            this.map = new Elt[size_x, size_y];
            this.dim = new Vector2(size_x, size_y);
            this.square = new Rectangle();
            this.square.Height = 58;
            this.square.Width = 155;
            this.square.X = (int)(this.square.Height);
            this.square.Y = (int)(this.square.Width);
            this.Load(((Main)this.Game).Sprites, ((Main)this.Game).SpriteBatch, ((Main)this.Game).SpriteFont);
        }

        public Vector2 getSize()
        {
            return this.dim;
        }

        public Elt getCase(int x, int y)
        {
            if (this.map != null)
                return this.map[x, y];
            throw new InvalidOperationException("Empty map");
        }

        public Rectangle getSquare()
        {
            return this.square;
        }

        public void unplug()
        {
            if (this.map != null)
            {
                this.map[this.square_details_pos.X, this.square_details_pos.Y].Selected = false;
                this.square_details_on = false;
            }
        }

        public void Load(SpriteManager cm, SpriteBatch sb, SpriteFont sf)
        {
            this.sb = sb;
            this.square_details = cm.GetSprite("Tiles/map_resources");
            this.sf = sf;
            this._wall[0] = cm.GetSprite("Background/wall");
            this._wall[1] = cm.GetSprite("Background/wall2");
            this._wall[2] = cm.GetSprite("Background/wall3");
            this._wall[3] = cm.GetSprite("Background/cloud");
            this._wall[4] = cm.GetSprite("Background/border");
            this._wall[5] = cm.GetSprite("Background/border2");
            this._wall[6] = cm.GetSprite("Background/top_border");
            this._wall[7] = cm.GetSprite("Background/top_border2");
            this._wall[8] = cm.GetSprite("Background/corner");

            for (int i = 0; i < this.dim.X; ++i)
                for (int j = 0; j < this.dim.Y; ++j)
                {
                    this.map[i, j] = new Elt(sb, new Point(i, j));
                    this.map[i, j].Load(cm);
                }

            //TODO REMOVE THIS
            foreach (Elt element in this.map)
            {
                if (p.Next(3) == 0)
                    element.Inventory.setAll((uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10), (uint)p.Next(10));
            }
        }

        public override void Initialize()
        {
            base.Initialize();
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            if (this.map == null)
                return;

            for (int i = 0; i < 5; ++i)
            {
                if (this.clouds[i].X >= 1300)
                    this.clouds[i].X = -400;
                else
                    this.clouds[i].X += 1;
            }

            if ((Keyboard.GetState().IsKeyDown(Keys.W) || Keyboard.GetState().IsKeyDown(Keys.Up)) && (this.view > 50 || this.edge[1]) && this.Vrep <= gameTime.TotalGameTime)
            {
                this.square.Y += 20;
                this.Vrep = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(30);
                this.edge[1] = false;
                this.edge[2] = true;
            }
            if ((Keyboard.GetState().IsKeyDown(Keys.S) || Keyboard.GetState().IsKeyDown(Keys.Down)) && (this.view > 50 || this.edge[2]) && this.Vrep <= gameTime.TotalGameTime)
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
                Vector2 pos = new Vector2(Mouse.GetState().X, Mouse.GetState().Y);
                for (int i = 0; i < this.dim.X; ++i)
                {
                    for (int j = 0; j < this.dim.Y; ++j)
                    {
                        if (this.map[i, j].isInPolygon(pos, this.square))
                        {
                            this.square_details_on = true;
                            this.square_setails_timer = gameTime.TotalGameTime + TimeSpan.FromSeconds(5);
                            this.map[this.square_details_pos.X, this.square_details_pos.Y].Selected = false;
                            this.map[j, i].Selected = true;
                            this.square_details_pos = new Point(j, i);
                            ((Main)this.Game).unplug();
                        }
                    }
                }
            }

            if (this.square_setails_timer <= gameTime.TotalGameTime)
            {
                this.map[this.square_details_pos.X, this.square_details_pos.Y].Selected = false;
                this.square_details_on = false;
            }
        }

        public override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);

            if (this.map == null)
                return;

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

            double factX = (200 * (this.square.Width / 155.0));
            double factY = (160 * (this.square.Height / 58.0));

            this.view = 0;
            int j = 0;
            int i = 0;

            for (i = 0; i < this.dim.X + 1; ++i, off.X += this.square.Width / 2, off.Y += this.square.Height / 2)
            {
                /* Bord superieur droit de la map */
                if (i != 0)
                {
                    p.X = ((int)this.dim.Y) * (this.square.Width / 2) + (off.X) + this.square.X;
                    p.Y = -((int)this.dim.Y) * (this.square.Height / 2) + (off.Y) + this.square.Y;
                    Rectangle tar2 = new Rectangle((int)(p.X - (int)(31 * (this.square.Width / 155.0))), (int)(p.Y - (int)(101 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                    if (this.screen.Intersects(tar2))
                        this._wall[i % 2].Draw(this.sb, tar2);
                }

                for (j = -1; j < (int)this.dim.Y + 1; ++j)
                {
                    /* Bord superieur gauche de la map */
                    if (j >= 1 && i == 1)
                    {
                        p.X = -j * (this.square.Width / 2) + this.square.X + ((int)this.dim.Y) * (this.square.Width / 2);
                        p.Y = j * (this.square.Height / 2) + this.square.Y - ((int)this.dim.Y) * (this.square.Height / 2);

                        Rectangle tar = new Rectangle((int)(p.X - (int)(33 * (this.square.Width / 155.0))), (int)(p.Y - (int)(103 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                        if (this.screen.Intersects(tar))
                            this._wall[2].Draw(this.sb, tar);
                    }

                    p.X = -j * (this.square.Width / 2) + (off.X) + this.square.X + ((int)this.dim.Y - 1) * (this.square.Width / 2);
                    p.Y = j * (this.square.Height / 2) + (off.Y) + this.square.Y - ((int)this.dim.Y - 1) * (this.square.Height / 2);
                    
                    /* Draw des case*/
                    if (i != 0 && j >= 0 && j < this.dim.Y)
                    {
                        Rectangle target = new Rectangle(p.X, p.Y, this.square.Width, this.square.Height);

                        if (this.Game.Window.ClientBounds.Contains(target))
                            this.view += 1;

                        if (this.screen.Intersects(target))
                            this.map[i - 1, j ].Draw(target);

                        if (this.map[i - 1, j ].Selected)
                        {
                            inventory = new string[7];
                            inventory[0] = this.map[i - 1, j ].Inventory.nourriture.ToString();
                            inventory[1] = this.map[i - 1, j ].Inventory.linemate.ToString();
                            inventory[2] = this.map[i - 1, j ].Inventory.deraumere.ToString();
                            inventory[3] = this.map[i - 1, j ].Inventory.sibur.ToString();
                            inventory[4] = this.map[i - 1, j ].Inventory.mendiane.ToString();
                            inventory[5] = this.map[i - 1, j ].Inventory.phiras.ToString();
                            inventory[6] = this.map[i - 1, j ].Inventory.thystame.ToString();
                        }
                    }
                    /* Bord inferieur gauche de la map*/
                    if (j == this.dim.Y)
                    {
                        Rectangle tar =  new Rectangle((int)(p.X - (this.square.Width / 2) - (int)(34 * (this.square.Width / 155.0))), (int)(p.Y - (this.square.Height / 2) - (int)(0 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                        if (i == 1 && this.screen.Intersects(tar))
                            this._wall[6].Draw(this.sb, tar);
                        tar = new Rectangle((int)(p.X - (int)(34 * (this.square.Width / 155.0))), (int)(p.Y - (int)(0 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                        if (i != 0 && this.screen.Intersects(tar))
                            this._wall[4].Draw(this.sb, tar);
                    }
                }
            }
            /* Bord inferieur droite de la map */
            for (j = (int)this.dim.Y; j >= 0; --j)
            {
                p.X = j * (this.square.Width / 2) + (off.X) + this.square.X;
                p.Y = -j * (this.square.Height / 2) + (off.Y) + this.square.Y;

                Rectangle tar = new Rectangle((int)(p.X - (int)(33 * (this.square.Width / 155.0))), (int)(p.Y - (int)(0 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                if (j == (int)this.dim.Y && this.screen.Intersects(tar))
                    this._wall[7].Draw(this.sb, tar);
                else if (this.screen.Intersects(tar))
                     this._wall[5].Draw(this.sb, tar);
             }

            p.X = -1 * (this.square.Width / 2) + ((this.square.Width / 2) * (int)this.dim.X) + this.square.X;
            p.Y = 1 * (this.square.Height / 2) + ((this.square.Height / 2) * (int)this.dim.X) + this.square.Y;

            Rectangle tar3 = new Rectangle((int)(p.X + (int)(45 * (this.square.Width / 155.0))), (int)(p.Y - (int)(8 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
            if (this.screen.Intersects(tar3))
                this._wall[8].Draw(this.sb, tar3);

            this.sb.End();
        }
    }
}
