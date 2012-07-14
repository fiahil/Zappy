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
using Microsoft.Xna.Framework.Input.Touch;
using Microsoft.Xna.Framework.Media;

namespace PhoneViewer
{
    /// <summary>
    /// Map class representing the whole terrain with cristals (Elt matrix)
    /// </summary>
    public class Map
    {
        Vector2 dim;
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
        GamePage Game;

        Rectangle square;
        public Rectangle Square
        {
            get { return this.square; }
            set { this.square.X = value.X; this.square.Y = value.Y; }
        }

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

        public Map(GamePage game)
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
            this.Game = game;
        }

        public void resizeMap(int size_x, int size_y)
        {
            this.map = new Elt[size_x, size_y];
            this.dim = new Vector2(size_x, size_y);
            this.square = new Rectangle();
            this.square.Height = 58;
            this.square.Width = 155;
            this.square.X = (int)(this.square.Height);
            this.square.Y = (int)(this.square.Width);
            this.Load(this.Game.Sprites, this.Game.SpriteBatch, this.Game.SpriteFont);
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

            TouchPanel.EnabledGestures = GestureType.FreeDrag | GestureType.Tap | GestureType.DoubleTap;
        }
        
        public void Update(GameTimerEventArgs gameTime)
        {
            if (this.map == null)
                return;

            for (int i = 0; i < 5; ++i)
            {
                if (this.clouds[i].X >= 1300)
                    this.clouds[i].X = -400;
                else
                    this.clouds[i].X += 1;
            }

            while (TouchPanel.IsGestureAvailable)
            {
                GestureSample gl = TouchPanel.ReadGesture();
                List<Player> plist = this.Game.Players;

                switch (gl.GestureType)
                {
                    case GestureType.DoubleTap:
                        // Player infos
                        foreach (Player elt in this.Game.Players)
                        {
                            Point p;
                            Point off;

                            off.X = (elt.getPos().X + 1) * (this.getSquare().Width / 2);
                            off.Y = (elt.getPos().X) * (this.getSquare().Height / 2);

                            p.X = ((int)this.getSize().Y - elt.getPos().Y - 1) * (this.getSquare().Width / 2) + off.X + this.getSquare().X;
                            p.Y = -((int)this.getSize().Y - elt.getPos().Y - 1) * (this.getSquare().Height / 2) + off.Y + this.getSquare().Y;

                            Rectangle bound = new Rectangle((int)(p.X + (int)(42 * (this.getSquare().Width / 155.0))),
                                (int)(p.Y - (int)(19 * (this.getSquare().Height / 58.0))),
                                (int)(elt.getBounds().Width * (this.getSquare().Width / 155.0)),
                                (int)(elt.getBounds().Height * (this.getSquare().Height / 58.0)));
                            if (bound.Contains(new Point((int)gl.Position.X, (int)gl.Position.Y)))
                            {
                                Game.Server.SendDatas("pin " + elt.Id + "\n");
                                this.Game.Inventory = elt;
                                this.Game.InventoryTimer = gameTime.TotalTime + TimeSpan.FromSeconds(10);
                            }
                        }
                        break;
                    case GestureType.Tap:
                        this.Game.Dot = new Vector2(gl.Position.X, gl.Position.Y);
                        for (int i = 0; i < this.dim.X; ++i)
                        {
                            for (int j = 0; j < this.dim.Y; ++j)
                            {
                                if (this.map[i, j].isInPolygon(new Vector2(this.Game.Dot.X, this.Game.Dot.Y), this.square, this))
                                {
                                    this.square_details_on = true;
                                    this.square_setails_timer = gameTime.TotalTime + TimeSpan.FromSeconds(10);
                                    this.map[this.square_details_pos.X, this.square_details_pos.Y].Selected = false;
                                    this.map[i, j].Selected = true;
                                    this.square_details_pos = new Point(i, j);
                                }
                            }
                        }
                        break;
                    case GestureType.FreeDrag:
                        this.square.Y += (int)(gl.Delta.Y * 1);
                        this.square.X += (int)(gl.Delta.X * 1);
                        break;
                }
            }

            if (this.square_setails_timer <= gameTime.TotalTime)
            {
                this.map[this.square_details_pos.X, this.square_details_pos.Y].Selected = false;
                this.square_details_on = false;
            }
        }

        private Rectangle getPos(int j, int posX, int posY, float factX, float factY)
        {
            Point p = new Point();

            p.X = this.square.X + ((int)this.dim.Y - j) * (this.square.Width / 2);
            p.Y = this.square.Y - ((int)this.dim.Y - j) * (this.square.Height / 2);
            return new Rectangle((int)(p.X - (int)(posX * (this.square.Width / 155.0))), (int)(p.Y - (int)(posY * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
        }
        private Rectangle getPos(int j, int offX, int offY, int posX, int posY, float factX, float factY)
        {
            Point p = new Point();

            p.X = offX + this.square.X + ((int)this.dim.Y - j) * (this.square.Width / 2);
            p.Y = offY + this.square.Y - ((int)this.dim.Y - j) * (this.square.Height / 2);
            return new Rectangle((int)(p.X - (int)(posX * (this.square.Width / 155.0))), (int)(p.Y - (int)(posY * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
        }

        public void Draw(GameTimerEventArgs gameTime)
        {
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

            float factX = (200 * (this.square.Width / 155.0f));
            float factY = (160 * (this.square.Height / 58.0f));

            this.view = 0;
            int j = 0;
            int i = 0;

            for (i = 0; i < this.dim.X + 1; ++i, off.X += this.square.Width / 2, off.Y += this.square.Height / 2)
            {

                for (j = -1; j < (int)this.dim.Y + 1; ++j)
                {
                    
                    /* Bord superieur droit de la map */                    
                    if (i != 0 && j == 0)
                    {
                        Rectangle target = this.getPos(j, off.X, off.Y, 31, 101, factX, factY);
                        if (this.screen.Intersects(target))
                            this._wall[i % 2].Draw(this.sb, target);
                    }

                    /* Bord superieur gauche de la map */
                    if (j >= 1 && i == 1)
                    {
                        Rectangle target = this.getPos(j, 33, 103, factX, factY);
                        if (this.screen.Intersects(target))
                            this._wall[2].Draw(this.sb, target);
                    }

                    if (i == 1)
                    {
                        /* Coin extreme droit de la map */
                        Rectangle tar = this.getPos((int)this.dim.Y + 1, 0, 0, 34, 0, factX, factY);
                        if (this.screen.Intersects(tar))
                            this._wall[6].Draw(this.sb, tar);
                    }
                    /* Draw des case*/
                    if (i != 0 && j >= 0 && j < this.dim.Y)
                    {
                        Rectangle target = this.getPos(j + 1, off.X, off.Y, 0, 0, this.square.Width, this.square.Height);
                        if (this.Game.screen.Contains(target))
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
                    if (j == this.dim.Y && i != 0)
                    {
                        Rectangle target = this.getPos(j + 1, off.X, off.Y, 34, 0, factX, factY);
                        if (this.screen.Intersects(target))
                            this._wall[4].Draw(this.sb, target);
                    }
                }
            }
            /* Bord inferieur droite de la map */
            for (j = 0 ; j < (int)this.dim.Y + 1; ++j)
            {
                Rectangle target = this.getPos(j, off.X, off.Y, 33, 0, factX, factY);
                if (j == 0 && this.screen.Intersects(target))
                    this._wall[7].Draw(this.sb, target);
                else if (this.screen.Intersects(target))
                     this._wall[5].Draw(this.sb, target);
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
