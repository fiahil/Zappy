using System;
using System.Collections.Generic;
using System.Linq;
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
    /// This is the main type for your game
    /// </summary>
    public class Main : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Map map;
        List<Player> plist;
        List<Egg> elist;
        List<string> tlist;
        SpriteFont sf;
        int t;
        Network server;
       
        Rectangle screen;
        Player inventory_details;
        TimeSpan inventory_timer;
        Sprite inventory_page;

        public Main()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            this.map = new Map(this);
            this.Components.Add(this.map);
            server = new Network();
            this.plist = new List<Player>();
            this.elist = new List<Egg>();
            this.tlist = new List<string>();
            this.screen = new Rectangle(0, 0, 1280, 720);
            this.inventory_details = null;
            this.inventory_timer = TimeSpan.Zero;
        }

        public void unplug()
        {
            this.inventory_details = null;
        }

        public List<Player> Players
        {
            get { return this.plist; }
        }

        public List<string> Teams
        {
            get { return this.tlist; }
        }

        public List<Egg> Eggs
        {
            get { return this.elist; }
        }

        public Map Map
        {
            get { return this.map; }
        }

        public SpriteBatch SpriteBatch
        {
            get { return this.spriteBatch; }
        }

        public SpriteFont SpriteFont
        {
            get { return this.sf; }
        }

        public int Time
        {
            set { this.t = value; }
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            base.Initialize();

            this.IsMouseVisible = true;
            this.Window.Title = "Zappy BBC";
            this.graphics.PreferMultiSampling = true;
            this.graphics.PreferredBackBufferWidth = 1280;
            this.graphics.PreferredBackBufferHeight = 720;
            this.graphics.ApplyChanges();

            //this.elist.Add(new Egg(this.Content, 0, 2, 2));

            //this.plist.Add(new Player(this.Content, 0)); //TO REMOVE
            //this.plist.Add(new Player(this.Content, 0)); //TO REMOVE
            //this.plist.Add(new Player(this.Content, 0)); //TO REMOVE
            //this.plist.Add(new Player(this.Content, 0)); //TO REMOVE
            //this.plist[0].setPos(2, 2);
            //this.plist[2].setPos(1, 2);
            //this.plist[3].setPos(2, 0);

            //this.plist[2].dir = Direction.WEST;
            //this.plist[3].dir = Direction.EAST;
            //this.plist[1].dir = Direction.SOUTH;
            //this.plist[0].setBroadcast("bite");
            //this.plist[1].setBroadcast("bite");
            //this.plist[2].setBroadcast("bite");
            //this.plist[3].setBroadcast("bite");

            //this.plist[0].st = Player.State.TAKE;
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);

            this.inventory_page = new Sprite(this.Content.Load<Texture2D>("Tiles/map_inventory"));
            this.sf = this.Content.Load<SpriteFont>("Font/Classic");

            this.map.resizeMap(50, 50);
            server.Initialize(this);
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            if (server.IsConnected())
                server.Update();

            base.Update(gameTime);

            if (Keyboard.GetState().IsKeyDown(Keys.Escape) || !server.IsConnected())
                this.Exit();

            this.plist.RemoveAll(delegate(Player p) { return p.State == Player.States.FINISHED; });

            if (Mouse.GetState().RightButton == ButtonState.Pressed)
            {
                Point ppmouse = new Point(Mouse.GetState().X, Mouse.GetState().Y);
                foreach (Player elt in this.plist)
                {
                    Point p;
                    Point off;

                    server.SendDatas("pin " + elt.Id + "\n");
                    off.X = (elt.getPos().X + 1) * (this.map.getSquare().Width / 2);
                    off.Y = (elt.getPos().X) * (this.map.getSquare().Height / 2);

                    p.X = elt.getPos().Y * (this.map.getSquare().Width / 2) + off.X + this.map.getSquare().X;
                    p.Y = -elt.getPos().Y * (this.map.getSquare().Height / 2) + off.Y + this.map.getSquare().Y;

                    Rectangle bound = new Rectangle((int)(p.X + (int)(42 * (this.map.getSquare().Width / 155.0))), (int)(p.Y - (int)(19 * (this.map.getSquare().Height / 58.0))), (int)(elt.getBounds().Width * (this.map.getSquare().Width / 155.0)), (int)(elt.getBounds().Height * (this.map.getSquare().Height / 58.0)));

                    if (bound.Contains(ppmouse))
                    {
                        this.inventory_details = elt;
                        this.inventory_timer = gameTime.TotalGameTime + TimeSpan.FromSeconds(5);
                        this.map.unplug();
                    }
                }
            }

            if (this.inventory_timer <= gameTime.TotalGameTime && this.inventory_details != null)
            {
                this.inventory_details = null;
            }
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.AliceBlue);
            base.Draw(gameTime);
            this.spriteBatch.Begin(SpriteSortMode.Deferred,BlendState.AlphaBlend);

            foreach (Egg eelt in elist)
            {
                eelt.Draw(gameTime, this.map.getSquare(), this.screen, this.spriteBatch);
            }

            foreach (Player pelt in plist)
            {
                pelt.Draw(gameTime, this.map.getSquare(), this.screen, this.spriteBatch);
            }

            if (this.inventory_details != null)
            {
                this.inventory_page.Draw(this.spriteBatch, new Rectangle(this.Window.ClientBounds.Width - this.inventory_page.getBounds().Width, 0, this.inventory_page.getBounds().Width, this.inventory_page.getBounds().Height));
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.nourriture.ToString(), new Vector2(1200, 100), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.linemate.ToString(), new Vector2(1200, 155), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.deraumere.ToString(), new Vector2(1200, 210), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.sibur.ToString(), new Vector2(1200, 265), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.mendiane.ToString(), new Vector2(1200, 325), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.phiras.ToString(), new Vector2(1200, 380), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.thystame.ToString(), new Vector2(1200, 440), Color.Black);
				this.spriteBatch.DrawString(this.sf, this.inventory_details.Level.ToString(), new Vector2(1120, 492), Color.Black);
				this.spriteBatch.DrawString(this.sf, this.inventory_details.Team, new Vector2(1120, 532), Color.Black);
            }
            if (this.map.SquareDetailsOn)
            {
                System.Diagnostics.Debug.Assert(this.map.Inventory != null);
                this.map.SquareDetails.Draw(this.spriteBatch, new Rectangle(base.Window.ClientBounds.Width - this.map.SquareDetails.getBounds().Width, 0, this.map.SquareDetails.getBounds().Width, this.map.SquareDetails.getBounds().Height));
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[0], new Vector2(1200, 100), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[1], new Vector2(1200, 155), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[2], new Vector2(1200, 210), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[3], new Vector2(1200, 265), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[4], new Vector2(1200, 325), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[5], new Vector2(1200, 380), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[6], new Vector2(1200, 440), Color.Black);
            }
            this.spriteBatch.End();
        }
    }
}
