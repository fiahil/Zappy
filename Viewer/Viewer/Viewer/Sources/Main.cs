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
        String teams;
        String scroll;
        TimeSpan time;

        bool end;
#if WINDOWS
        MusicManager mm;
        SoundManager sounds;
#endif
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Map map;
        List<Player> plist;
        List<Egg> elist;
        List<string> tlist;
        SpriteFont sf;
        SpriteFont sf_bc;
        SpriteFont vic;
        int t;
#if WINDOWS
        Network server;
#endif
        String winner;

        Rectangle screen;
        Player inventory_details;
        TimeSpan inventory_timer;
        Sprite inventory_page;
        Sprite team_detail;
        Sprite bc_box;
        Sprite tm_box;
        Queue<string> lbc;
        KeyboardState oldState;

        int followedId;
        Player followed;
        public Player Followed
        {
            get { return this.followed; }
            set
            {
                this.followed = value;
#if WINDOWS
                if (value != null)
                    this.followedId = this.plist.FindIndex(p => value.Id == p.Id);
#endif
#if XBOX
                if (value != null)
                {
                    int i = 0;
                    int j = 0;
                    foreach (var item in this.plist)
                    {
                        if (item.Id == value.Id)
                            i = j;
                        j++;
                    }
                    this.followedId = i;
                }
#endif
            }
        }
        SpriteManager sm;
        public SpriteManager Sprites
        {
            get { return this.sm; }
        }
        public Main()
        {
            this.time = TimeSpan.Zero;
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            this.map = new Map(this);
            this.Components.Add(this.map);
#if WINDOWS
            server = new Network();
#endif
            this.plist = new List<Player>();
            this.elist = new List<Egg>();
            this.tlist = new List<string>();
            this.lbc = new Queue<string>();
            this.screen = new Rectangle(0, 0, 1280, 720);
            this.inventory_details = null;
            this.inventory_timer = TimeSpan.Zero;
            this.dot = new Vector2(640, 360);
            this.followed = null;
            this.followedId = 0;
            this.oldState = Keyboard.GetState();
            this.end = false;
        }


        Vector2 dot;
        public Vector2 Dot
        {
            set { dot = value; }
            get { return dot; }
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

        public bool End
        {
            set { this.end = value; }
        }

        public String Winner
        {
            set { this.winner = value; }
        }

#if WINDOWS
        public SoundManager Sounds
        {
            get { return this.sounds; }
        }
#endif
        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>

        public void addBroadcast(string team, string msg)
        {
            if (team.Length > 5)
                team = team.Remove(5);
            if (msg.Length > 40)
            {
                msg = msg.Remove(37);
                msg += "...";
            }
            if (this.lbc.Count >= 3)
                this.lbc.Dequeue();
            this.lbc.Enqueue(team + " : " + msg);
        }

        protected override void Initialize()
        {
            base.Initialize();

            this.IsMouseVisible = true;
            this.Window.Title = "Zappy BBC";
            this.graphics.PreferMultiSampling = true;
            this.graphics.PreferredBackBufferWidth = 1280;
            this.graphics.PreferredBackBufferHeight = 720;
            this.graphics.ApplyChanges();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);

#if WINDOWS
            this.mm = new MusicManager(this.Content);
            this.sounds = new SoundManager(this.Content);
#endif
            this.sm = new SpriteManager(this.Content);
            this.inventory_page = sm.GetSprite("Tiles/map_inventory");
            this.team_detail = sm.GetSprite("Tiles/team_detail");
            this.bc_box = sm.GetSprite("Tiles/bc_box");
            this.tm_box = sm.GetSprite("Tiles/tm_box");
            this.sf = this.Content.Load<SpriteFont>("Font/Classic");
            this.sf_bc = this.Content.Load<SpriteFont>("Font/Broadcast");
            this.vic = this.Content.Load<SpriteFont>("Font/victory");

            this.map.resizeMap(10, 10);
#if WINDOWS
            server.Initialize(this);
#endif
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
        }

        private void InitTeamString()
        {
            foreach (String team in this.Teams)
                this.teams += team + " - ";
            this.teams = this.teams.Remove(this.teams.Length - 3, 3);
            this.teams = this.teams.Insert(this.teams.Length, "                    ");
            this.scroll = this.teams.Substring(0, 20);
        }

        private void DisplayTeams(GameTime gameTime)
        {
            if (this.time == TimeSpan.Zero || this.time <= gameTime.TotalGameTime)
            {
                char tmp;

                this.scroll = this.scroll.Remove(0, 1);
                this.scroll = this.scroll + this.teams[20];
                tmp = this.teams[0];
                this.teams = this.teams.Remove(0, 1);
                this.teams = this.teams + tmp;
                this.time = gameTime.TotalGameTime + TimeSpan.FromMilliseconds(75);
            }
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
#if WINDOWS
            if (server.IsConnected())
            {
                server.Update();
                if (this.Teams.Count > 0 && this.teams == null)
                    this.InitTeamString();
            }
#endif

            base.Update(gameTime);

#if WINDOWS
            mm.Update();

            if (Keyboard.GetState().IsKeyDown(Keys.Escape) || !server.IsConnected() || GamePad.GetState(PlayerIndex.One).IsButtonDown(Buttons.Y))
                this.Exit();
#endif
#if XBOX
            if (GamePad.GetState(PlayerIndex.One).IsButtonDown(Buttons.Y))
                this.Exit();
#endif

            Vector2 test = GamePad.GetState(PlayerIndex.One).ThumbSticks.Left * 5;

            this.dot.X += test.X;
            this.dot.Y -= test.Y;

#if WINDOWS
            this.plist.RemoveAll(delegate(Player p) { return p.State == Player.States.FINISHED; });

            if (oldState.IsKeyUp(Keys.C) && Keyboard.GetState().IsKeyDown(Keys.C))
            {
                mm.Mute();
                sounds.Mute();
            }
#endif
#if XBOX
            try
            {
                for (Player P = null; (P = this.plist.First(p => p.State == Player.States.FINISHED)) != null; )
                {
                    this.plist.Remove(P);
                }
            }
            catch { }
#endif

            if (this.end == false)
            {
                if ((oldState.IsKeyUp(Keys.PageDown) && Keyboard.GetState().IsKeyDown(Keys.PageDown)) ||
                    GamePad.GetState(PlayerIndex.One).IsButtonDown(Buttons.RightTrigger))
                {
                    try
                    {
                        this.followed = this.plist[(++this.followedId) % this.plist.Count];
                    }
                    catch
                    {
                        this.followed = null;
                    }
                }
                if ((oldState.IsKeyUp(Keys.PageUp) && Keyboard.GetState().IsKeyDown(Keys.PageUp)) ||
                    GamePad.GetState(PlayerIndex.One).IsButtonDown(Buttons.LeftTrigger))
                {
                    try
                    {
                        this.followed = this.plist[(--this.followedId + this.plist.Count) % this.plist.Count];
                    }
                    catch
                    {
                        this.followed = null;
                    }
                }
                if (Mouse.GetState().RightButton == ButtonState.Pressed || GamePad.GetState(PlayerIndex.One).IsButtonDown(Buttons.B))
                {
                    if (Mouse.GetState().RightButton == ButtonState.Pressed)
                        this.dot = new Vector2(Mouse.GetState().X, Mouse.GetState().Y);
                    foreach (Player elt in this.plist)
                    {
                        Point p;
                        Point off;

#if WINDOWS
                        server.SendDatas("pin " + elt.Id + "\n");
#endif
                        off.X = (elt.getPos().X + 1) * (this.map.getSquare().Width / 2);
                        off.Y = (elt.getPos().X) * (this.map.getSquare().Height / 2);

                        p.X = ((int)this.map.getSize().Y - elt.getPos().Y - 1) * (this.map.getSquare().Width / 2) + off.X + this.map.getSquare().X;
                        p.Y = -((int)this.map.getSize().Y - elt.getPos().Y - 1) * (this.map.getSquare().Height / 2) + off.Y + this.map.getSquare().Y;

                        Rectangle bound = new Rectangle((int)(p.X + (int)(42 * (this.map.getSquare().Width / 155.0))), (int)(p.Y - (int)(19 * (this.map.getSquare().Height / 58.0))), (int)(elt.getBounds().Width * (this.map.getSquare().Width / 155.0)), (int)(elt.getBounds().Height * (this.map.getSquare().Height / 58.0)));

                        if (bound.Contains(new Point((int)this.dot.X, (int)this.dot.Y)))
                        {
                            this.inventory_details = elt;
                            this.inventory_timer = gameTime.TotalGameTime + TimeSpan.FromSeconds(10);
                            if (Keyboard.GetState().IsKeyDown(Keys.LeftControl) || GamePad.GetState(PlayerIndex.One).IsButtonDown(Buttons.LeftShoulder))
                            {
                                this.followed = elt;
                                Rectangle r = new Rectangle();
                                r.X = -(-elt.Pos.Y * (this.map.getSquare().Width / 2) + (elt.getPos().X + 1) * (this.map.getSquare().Width / 2) + ((int)map.getSize().Y - 1) * (this.map.getSquare().Width / 2) - 620);
                                r.Y = -(elt.Pos.Y * (this.map.getSquare().Height / 2) + (elt.getPos().X) * (this.map.getSquare().Height / 2) - ((int)map.getSize().Y - 1) * (this.map.getSquare().Height / 2) - 360);
                                this.map.Square = r;
                            }
                            else
                            {
                                this.followed = null;
                            }
                        }
                    }
                }

                if (Keyboard.GetState().IsKeyDown(Keys.Space))
                    this.followed = null;

                if (this.inventory_timer <= gameTime.TotalGameTime && this.inventory_details != null && this.followed == null)
                {
                    this.inventory_details = null;
                }
            }
#if WINDOWS
            else
                this.mm.PlayEnd();
#endif
            this.oldState = Keyboard.GetState();
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.AliceBlue);
            base.Draw(gameTime);
            this.spriteBatch.Begin(SpriteSortMode.Deferred, BlendState.AlphaBlend);
            if (this.end == false)
            {
                foreach (Egg eelt in elist)
                {
                    eelt.Draw(gameTime, this.map.getSquare(), this.screen, this.spriteBatch, this.map);
                }

                foreach (Player pelt in plist)
                {
                    pelt.Draw(gameTime, this.map.getSquare(), this.screen, this.spriteBatch, this.map);
                }

                if (this.inventory_details != null)
                {
                    this.inventory_page.Draw(this.spriteBatch, new Rectangle(0, this.Window.ClientBounds.Height - this.inventory_page.getBounds().Height, this.inventory_page.getBounds().Width, this.inventory_page.getBounds().Height));
                    this.bc_box.Draw(this.spriteBatch, new Rectangle(this.inventory_page.getBounds().Width - 54, this.Window.ClientBounds.Height - this.bc_box.getBounds().Height - 10, this.bc_box.getBounds().Width, this.bc_box.getBounds().Height));
                    this.team_detail.Draw(this.spriteBatch, new Rectangle(this.Window.ClientBounds.Width - this.team_detail.getBounds().Width, this.Window.ClientBounds.Height - this.team_detail.getBounds().Height, this.team_detail.getBounds().Width, this.team_detail.getBounds().Height));
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.nourriture.ToString(), new Vector2(368 - (this.inventory_details.Inventory.nourriture.ToString().Length * 7), 515), Color.White);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.linemate.ToString(), new Vector2(205, 615), Color.Black);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.deraumere.ToString(), new Vector2(205, 650), Color.Black);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.sibur.ToString(), new Vector2(205, 685), Color.Black);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.mendiane.ToString(), new Vector2(319, 615), Color.Black);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.phiras.ToString(), new Vector2(319, 650), Color.Black);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.thystame.ToString(), new Vector2(319, 685), Color.Black);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Level.ToString(), new Vector2(278, 555), Color.Black);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Team, new Vector2(150, 555), Color.Black);
                    this.spriteBatch.DrawString(this.sf, this.inventory_details.Team, new Vector2(this.Window.ClientBounds.Width - 200, 555), Color.Black);
                    int sizeTeam = 0;
                    int maxLvl = 0;
                    int avgLvl = 0;

                    foreach (var item in this.plist)
                    {
                        if (item.Team == this.inventory_details.Team)
                        {
                            sizeTeam += 1;
                            if (item.Level > maxLvl)
                                maxLvl = item.Level;
                            avgLvl += item.Level;
                        }
                    }
                    if (sizeTeam != 0)
                        avgLvl /= sizeTeam;
                    else
                        avgLvl = 0;
                    this.spriteBatch.DrawString(this.sf, sizeTeam.ToString(), new Vector2(this.Window.ClientBounds.Width - 150, 590), Color.Black);
                    this.spriteBatch.DrawString(this.sf, maxLvl.ToString(), new Vector2(this.Window.ClientBounds.Width - 100, 655), Color.Black);
                    this.spriteBatch.DrawString(this.sf, avgLvl.ToString(), new Vector2(this.Window.ClientBounds.Width - 100, 680), Color.Black);

                    int dec = 0;
                    foreach (var item in this.lbc)
                    {
                        this.spriteBatch.DrawString(this.sf_bc, item, new Vector2(415, 630 + dec), Color.White);
                        dec += 20;
                    }

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
                if (GamePad.GetState(PlayerIndex.One).IsConnected)
                    sm.GetSprite("Tiles/cursor").Draw(this.spriteBatch, new Rectangle((int)(dot.X - 25), (int)(dot.Y - 25), 50, 50));
                this.tm_box.Draw(this.spriteBatch, new Rectangle(0, 0, this.tm_box.getBounds().Width, this.tm_box.getBounds().Height));
                if (this.scroll != null)
                {
                    this.DisplayTeams(gameTime);
                    this.spriteBatch.DrawString(this.sf, this.scroll, new Vector2(12, 12), Color.White);
                }
            }
            else
            {
                sm.GetSprite("Background/Victory").Draw(this.spriteBatch, new Rectangle(0, 0, 1280, 720));
                this.spriteBatch.DrawString(this.vic, "Team", new Vector2(640 - (this.vic.MeasureString("Team").X / 2), 110), Color.Black);
                this.spriteBatch.DrawString(this.vic, this.winner, new Vector2(640 - (this.vic.MeasureString(this.winner).X / 2), 190), Color.Red);
                this.spriteBatch.DrawString(this.vic, "is victorious", new Vector2(415, 270), Color.Black);
            }
            this.spriteBatch.End();
        }
    }
}
