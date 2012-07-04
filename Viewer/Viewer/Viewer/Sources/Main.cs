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
        public Map map;
        public List<Player> plist;
        public List<Egg> elist;
        public List<string> tlist;
        public int t;
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
            server.Initialize(this);
            this.plist = new List<Player>();
            this.screen = new Rectangle(0, 0, 1280, 720);
            this.inventory_details = null;
            this.inventory_timer = TimeSpan.Zero;
        }

        public void unplug()
        {
            this.inventory_details = null;
        }

        public List<Player> getPlayers()
        {
            return this.plist;
        }

        public List<Egg> getEggs()
        {
            return this.elist;
        }

        public Map getMap()
        {
            return this.map;
        }

        public SpriteBatch getSb()
        {
            return this.spriteBatch;
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

            this.plist.Add(new Player(this.Content)); //TO REMOVE
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);

            this.inventory_page = new Sprite(this.Content.Load<Texture2D>("Tiles/map_inventory"));
            this.map.resizeMap(50, 50);
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
            server.Update();

            base.Update(gameTime);

            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
                this.Exit();

            if (Mouse.GetState().RightButton == ButtonState.Pressed)
            {
                Point ppmouse = new Point(Mouse.GetState().X, Mouse.GetState().Y);
                foreach (Player elt in this.plist)
                {
                    if (elt.getBounds().Contains(ppmouse))
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

            foreach (Player pelt in plist)
            {
                pelt.Draw(gameTime, this.map.getSquare(), this.spriteBatch);
            }

            if (this.inventory_details != null)
                this.inventory_page.Draw(this.spriteBatch, new Rectangle(this.Window.ClientBounds.Width - this.inventory_page.getBounds().Width, 0, this.inventory_page.getBounds().Width, this.inventory_page.getBounds().Height));
            this.spriteBatch.End();
        }
    }
}
