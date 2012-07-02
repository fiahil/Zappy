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
        Sprite[] tiles;

        Sprite[] nourriture;
        Sprite[] linemate;
        Sprite[] deraumere;
        Sprite[] sibur;
        Sprite[] mendiane;
        Sprite[] phiras;
        Sprite[] thystame;

        int off;

        public Inventory iv;
        public Rectangle Bounds;

        static Random rd = new Random();

        public Elt(SpriteBatch sb)
        {
            this.tiles = new Sprite[3];

            this.nourriture = new Sprite[2];
            this.linemate = new Sprite[2];
            this.deraumere = new Sprite[2];
            this.sibur = new Sprite[2];
            this.mendiane = new Sprite[2];
            this.phiras = new Sprite[2];
            this.thystame = new Sprite[2];

            this.sb = sb;
            this.off = rd.Next(3);

            this.iv = new Inventory();
        }

        public void Load(ContentManager cm)
        {
            this.tiles[0] = new Sprite(cm.Load<Texture2D>("Tiles/base1"));
            this.tiles[1] = new Sprite(cm.Load<Texture2D>("Tiles/base2"));
            this.tiles[2] = new Sprite(cm.Load<Texture2D>("Tiles/base3"));

            this.nourriture[0] = new Sprite(cm.Load<Texture2D>("Resources/nourriture_small"));
            this.nourriture[1] = new Sprite(cm.Load<Texture2D>("Resources/nourriture_big"));

            this.linemate[0] = new Sprite(cm.Load<Texture2D>("Resources/linemate_small"));
            this.linemate[1] = new Sprite(cm.Load<Texture2D>("Resources/linemate_big"));

            this.deraumere[0] = new Sprite(cm.Load<Texture2D>("Resources/deraumere_small"));
            this.deraumere[1] = new Sprite(cm.Load<Texture2D>("Resources/deraumere_big"));

            this.sibur[0] = new Sprite(cm.Load<Texture2D>("Resources/sibur_small"));
            this.sibur[1] = new Sprite(cm.Load<Texture2D>("Resources/sibur_big"));

            this.mendiane[0] = new Sprite(cm.Load<Texture2D>("Resources/mendiane_small"));
            this.mendiane[1] = new Sprite(cm.Load<Texture2D>("Resources/mendiane_big"));

            this.phiras[0] = new Sprite(cm.Load<Texture2D>("Resources/phiras_small"));
            this.phiras[1] = new Sprite(cm.Load<Texture2D>("Resources/phiras_big"));

            this.thystame[0] = new Sprite(cm.Load<Texture2D>("Resources/thystame_small"));
            this.thystame[1] = new Sprite(cm.Load<Texture2D>("Resources/thystame_big"));

            this.Bounds = tiles[0].getBounds();
        }

        public void Draw(Rectangle square)
        {
            this.tiles[this.off].Draw(sb, square);

            if (this.iv.nourriture > 0 && this.iv.nourriture < 5)
                this.nourriture[0].Draw(sb, new Rectangle(square.X + (int)(98 * (square.Width / 155.0)), square.Y + (int)(18 * (square.Height / 58.0)), (int)(54.0 * (square.Width / 155.0 * 0.45)), (int)(48.0 * (square.Height / 58.0 * 0.45))));
            if (this.iv.nourriture >= 5)
                this.nourriture[1].Draw(sb, new Rectangle(square.X + (int)(98 * (square.Width / 155.0)), square.Y + (int)(16 * (square.Height / 58.0)), (int)(66.0 * (square.Width / 155.0 * 0.45)), (int)(54.0 * (square.Height / 58.0 * 0.45))));

            if (this.iv.mendiane > 0 && this.iv.mendiane < 5)
                this.mendiane[0].Draw(sb, new Rectangle(square.X + (int)(42 * (square.Width / 155.0)), square.Y + (int)(9 * (square.Height / 58.0)), (int)(57.0 * (square.Width / 155.0 * 0.45)), (int)(50.0 * (square.Height / 58.0 * 0.45))));
            if (this.iv.mendiane >= 5)
                this.mendiane[1].Draw(sb, new Rectangle(square.X + (int)(45 * (square.Width / 155.0)), square.Y + (int)(7 * (square.Height / 58.0)), (int)(66.0 * (square.Width / 155.0 * 0.45)), (int)(52.0 * (square.Height / 58.0 * 0.45))));

            if (this.iv.phiras > 0 && this.iv.phiras < 5)
                this.phiras[0].Draw(sb, new Rectangle(square.X + (int)(62 * (square.Width / 155.0)), square.Y + (int)(18 * (square.Height / 58.0)), (int)(54.0 * (square.Width / 155.0 * 0.45)), (int)(46.0 * (square.Height / 58.0 * 0.45))));
            if (this.iv.phiras >= 5)
                this.phiras[1].Draw(sb, new Rectangle(square.X + (int)(62 * (square.Width / 155.0)), square.Y + (int)(15 * (square.Height / 58.0)), (int)(67.0 * (square.Width / 155.0 * 0.45)), (int)(53.0 * (square.Height / 58.0 * 0.45))));

            if (this.iv.thystame > 0 && this.iv.thystame < 5)
                this.thystame[0].Draw(sb, new Rectangle(square.X + (int)(80 * (square.Width / 155.0)), square.Y + (int)(25 * (square.Height / 58.0)), (int)(57.0 * (square.Width / 155.0 * 0.45)), (int)(51.0 * (square.Height / 58.0 * 0.45))));
            if (this.iv.thystame >= 5)
                this.thystame[1].Draw(sb, new Rectangle(square.X + (int)(80 * (square.Width / 155.0)), square.Y + (int)(24 * (square.Height / 58.0)), (int)(66.0 * (square.Width / 155.0 * 0.45)), (int)(53.0 * (square.Height / 58.0 * 0.45))));

            if (this.iv.linemate > 0 && this.iv.linemate < 5)
                this.linemate[0].Draw(sb, new Rectangle(square.X + (int)(20 * (square.Width / 155.0)), square.Y + (int)(16 * (square.Height / 58.0)), (int)(62.0 * (square.Width / 155.0 * 0.45)), (int)(55.0 * (square.Height / 58.0 * 0.45))));
            if (this.iv.linemate >= 5)
                this.linemate[1].Draw(sb, new Rectangle(square.X + (int)(22 * (square.Width / 155.0)), square.Y + (int)(17 * (square.Height / 58.0)), (int)(66.0 * (square.Width / 155.0 * 0.45)), (int)(53.0 * (square.Height / 58.0 * 0.45))));

            if (this.iv.deraumere > 0 && this.iv.deraumere < 5)
                this.deraumere[0].Draw(sb, new Rectangle(square.X + (int)(42 * (square.Width / 155.0)), square.Y + (int)(28 * (square.Height / 58.0)), (int)(55.0 * (square.Width / 155.0 * 0.45)), (int)(45.0 * (square.Height / 58.0 * 0.45))));
            if (this.iv.deraumere >= 5)
                this.deraumere[1].Draw(sb, new Rectangle(square.X + (int)(40 * (square.Width / 155.0)), square.Y + (int)(22 * (square.Height / 58.0)), (int)(67.0 * (square.Width / 155.0 * 0.45)), (int)(58.0 * (square.Height / 58.0 * 0.45))));

            if (this.iv.sibur > 0 && this.iv.sibur < 5)
                this.sibur[0].Draw(sb, new Rectangle(square.X + (int)(64 * (square.Width / 155.0)), square.Y + (int)(36 * (square.Height / 58.0)), (int)(55.0 * (square.Width / 155.0 * 0.45)), (int)(43.0 * (square.Height / 58.0 * 0.45))));
            if (this.iv.sibur >= 5)
                this.sibur[1].Draw(sb, new Rectangle(square.X + (int)(57 * (square.Width / 155.0)), square.Y + (int)(25 * (square.Height / 58.0)), (int)(72.0 * (square.Width / 155.0 * 0.45)), (int)(67.0 * (square.Height / 58.0 * 0.45))));
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

        Sprite square_details;
        bool square_details_on;
        TimeSpan square_setails_timer;
        Sprite[] _wall;
        Point[] clouds;

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

        public Rectangle getSquare()
        {
            return this.square;
        }

        public void Load(ContentManager cm, SpriteBatch sb)
        {
            this.sb = sb;

            this.square_details = new Sprite(this.Game.Content.Load<Texture2D>("Tiles/map_resources"));
            this._wall[0] = new Sprite(cm.Load<Texture2D>("Background/wall"));
            this._wall[1] = new Sprite(cm.Load<Texture2D>("Background/wall2"));
            this._wall[2] = new Sprite(cm.Load<Texture2D>("Background/wall3"));
            this._wall[3] = new Sprite(cm.Load<Texture2D>("Background/cloud"));

            for (int i = 0; i < this.dim.X; ++i)
                for (int j = 0; j < this.dim.Y; ++j)
                {
                    this.map[i, j] = new Elt(sb);
                    this.map[i, j].Load(cm);
                }
            this.map[0,0].iv.setAll(4,4,6,6,6,6,6);
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
                Vector2 pos = new Vector2(Mouse.GetState().X, Mouse.GetState().Y);
                Rectangle targetz = this.map[0, 0].Bounds;
                targetz.X += this.square.X;
                targetz.Y += this.square.Y;

                Vector2 pp = new Vector2(2, 2);
                Vector2 p = new Vector2(pp.X * (this.square.Width / 2) + ((pp.Y + 1) * (this.square.Width / 2)), -pp.X * (this.square.Height / 2) + ((pp.Y + 1)* (this.square.Height / 2)));

                Polygon target = new Polygon(new Vector2[]
                {
                    new Vector2((this.square.X + p.X) + this.square.Width / 2, (this.square.Y + p.Y)),
                    new Vector2((this.square.X + p.X) + this.square.Width, (this.square.Y + p.Y) + this.square.Height / 2),
                    new Vector2((this.square.X + p.X) + this.square.Width / 2, (this.square.Y + p.Y) + this.square.Height),
                    new Vector2((this.square.X + p.X), (this.square.Y + p.Y) + this.square.Height / 2)
                });

                if (target.Contains(pos))
                {
                    this.square_details_on = true;
                    this.square_setails_timer = gameTime.TotalGameTime + TimeSpan.FromSeconds(5);
                }
            }
            if (this.square_setails_timer <= gameTime.TotalGameTime)
                this.square_details_on = false;
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

                        this.map[i - 1, j].Draw(target);
                    }

                    if (i == 1)
                    {
                        p.X = j * (this.square.Width / 2) + this.square.X;
                        p.Y = -j * (this.square.Height / 2) + this.square.Y;
                        Rectangle tar = new Rectangle((int)(p.X - (int)(33 * (this.square.Width / 155.0))), (int)(p.Y - (int)(103 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                        this._wall[2].Draw(this.sb, tar);
                    }
                }
                if (i != 0)
                {
                    p.X = ((int)this.dim.Y - 1 - j) * (this.square.Width / 2) + (off.X) + this.square.X;
                    p.Y = - ((int)this.dim.Y - 1 - j) * (this.square.Height / 2) + (off.Y) + this.square.Y;
                    Rectangle tar2 = new Rectangle((int)(p.X - (int)(31 * (this.square.Width / 155.0))), (int)(p.Y - (int)(101 * (this.square.Height / 58.0))), (int)(factX), (int)(factY));
                    this._wall[i % 2].Draw(this.sb, tar2);
                }
            }
            if (this.square_details_on)
                this.square_details.Draw(this.sb, new Rectangle(this.Game.Window.ClientBounds.Width - this.square_details.getBounds().Width, 0, this.square_details.getBounds().Width, this.square_details.getBounds().Height));

            this.sb.End();
        }
    }
}
