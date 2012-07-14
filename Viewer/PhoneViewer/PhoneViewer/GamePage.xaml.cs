using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace PhoneViewer
{
    public partial class GamePage : PhoneApplicationPage
    {
        ContentManager contentManager;
        GameTimer timer;
        SpriteBatch spriteBatch;

        Map map;
        List<Player> plist;
        List<Egg> elist;
        List<string> tlist;
        SpriteFont sf;
        SpriteFont sf_bc;
        int t;
        Network server;
        public Network Server
        {
            get { return server; }
        }

        public Microsoft.Xna.Framework.Rectangle screen;

        Sprite inventory_page;
        Sprite team_detail;
        Sprite bc_box;
        Queue<string> lbc;

        Player inventory_details;
        TimeSpan inventory_timer;
        public Player Inventory
        {
            set { this.inventory_details = value; }
        }
        public TimeSpan InventoryTimer
        {
            set { this.inventory_timer = value; }
        }

        SpriteManager sm;
        public SpriteManager Sprites
        {
            get { return this.sm; }
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

        public GamePage()
        {
            InitializeComponent();

            // Obtenir le gestionnaire de contenu de l’application
            contentManager = (Application.Current as App).Content;

            // Créer un minuteur pour cette page
            timer = new GameTimer();
            timer.UpdateInterval = TimeSpan.FromTicks(333333);
            timer.Update += OnUpdate;
            timer.Draw += OnDraw;

            this.map = new Map(this);
            server = new Network();
            this.plist = new List<Player>();
            this.elist = new List<Egg>();
            this.tlist = new List<string>();
            this.lbc = new Queue<string>();
            this.screen = new Microsoft.Xna.Framework.Rectangle(0, 0, 800, 480);
            this.inventory_details = null;
            this.inventory_timer = TimeSpan.Zero;
            this.dot = new Vector2(640, 360);
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            // Définir le mode de partage de la carte graphique pour activer le partage du rendu XNA
            SharedGraphicsDeviceManager.Current.GraphicsDevice.SetSharingMode(true);

            // Créer un SpriteBatch, qui peut être utilisé pour dessiner des textures.
            spriteBatch = new SpriteBatch(SharedGraphicsDeviceManager.Current.GraphicsDevice);

            // TODO: utilisez this.Content pour charger votre contenu de jeu ici
            this.sm = new SpriteManager(this.contentManager);
            this.inventory_page = sm.GetSprite("Tiles/map_inventory");
            this.team_detail = sm.GetSprite("Tiles/team_detail");
            this.bc_box = sm.GetSprite("Tiles/bc_box");
            this.sf = this.contentManager.Load<SpriteFont>("Font/Classic");
            this.sf_bc = this.contentManager.Load<SpriteFont>("Font/Broadcast");

            //this.map.resizeMap(10, 10);
            server.Initialize(this);

            if (!server.IsConnected())
            {
                MessageBox.Show("Connection Error", server.Error(), MessageBoxButton.OK);
                this.NavigationService.GoBack();
            }
            // Démarrer le minuteur
            timer.Start();

        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            // Arrêter le minuteur
            timer.Stop();

            this.server.Socket.Close();
            // Définir le mode de partage de la carte graphique pour désactiver le partage du rendu XNA
            SharedGraphicsDeviceManager.Current.GraphicsDevice.SetSharingMode(false);

            base.OnNavigatedFrom(e);
        }

        /// <summary>
        /// Permet à la page d’exécuter la logique de mise à jour du monde,
        /// de vérifier les collisions, de gérer les entrées et de lire l’audio.
        /// </summary>
        private void OnUpdate(object sender, GameTimerEventArgs e)
        {
            // TODO: Ajouter votre logique de mise à jour ici
            this.server.Update();
            this.map.Update(e);
            try
            {
                for (Player P = null; (P = this.plist.First(p => p.State == Player.States.FINISHED)) != null; )
                {
                    this.plist.Remove(P);
                }
            }
            catch { }

            if (this.inventory_timer <= e.TotalTime && this.inventory_details != null)
            {
                this.inventory_details = null;
            }
        }

        /// <summary>
        /// Permet à la page de se dessiner.
        /// </summary>
        private void OnDraw(object sender, GameTimerEventArgs e)
        {
            SharedGraphicsDeviceManager.Current.GraphicsDevice.Clear(Color.AliceBlue);

            // TODO: Ajouter votre code de dessin ici
            this.map.Draw(e);

            this.spriteBatch.Begin(SpriteSortMode.Deferred, BlendState.AlphaBlend);
            foreach (Egg eelt in elist)
            {
                eelt.Draw(e, this.map.getSquare(), this.screen, this.spriteBatch, this.map);
            }

            foreach (Player pelt in plist)
            {
                pelt.Draw(e, this.map.getSquare(), this.screen, this.spriteBatch, this.map);
            }

            if (this.inventory_details != null)
            {
                this.inventory_page.Draw(this.spriteBatch, new Microsoft.Xna.Framework.Rectangle(0, this.screen.Height - (int)(this.inventory_page.getBounds().Height / 1.5), (int)(this.inventory_page.getBounds().Width / 1.5), (int)(this.inventory_page.getBounds().Height / 1.5)));
                this.bc_box.Draw(this.spriteBatch, new Microsoft.Xna.Framework.Rectangle((int)((this.inventory_page.getBounds().Width - 54) / 1.5), this.screen.Height - (int)((this.bc_box.getBounds().Height - 10) / 1.5), (int)(this.bc_box.getBounds().Width / 1.20), (int)(this.bc_box.getBounds().Height / 1.5)));
                this.team_detail.Draw(this.spriteBatch, new Microsoft.Xna.Framework.Rectangle(this.screen.Width - (int)(this.team_detail.getBounds().Width / 1.5), this.screen.Height - (int)(this.team_detail.getBounds().Height / 1.5), (int)(this.team_detail.getBounds().Width / 1.5), (int)(this.team_detail.getBounds().Height / 1.5)));
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.nourriture.ToString(), new Vector2(368 - (this.inventory_details.Inventory.nourriture.ToString().Length * 7), 515), Color.White);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.linemate.ToString(), new Vector2((int)(205 / 1.5), 410), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.deraumere.ToString(), new Vector2((int)(205 / 1.5), 433), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.sibur.ToString(), new Vector2((int)(205 / 1.5), 457), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.mendiane.ToString(), new Vector2((int)(319 / 1.5), 410), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.phiras.ToString(), new Vector2((int)(319 / 1.5), 433), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Inventory.thystame.ToString(), new Vector2((int)(319 / 1.5), 457), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Level.ToString(), new Vector2((int)(278 / 1.5), 370), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Team, new Vector2((int)(150 / 1.5), 370), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.inventory_details.Team, new Vector2(this.screen.Width - (int)(200 / 1.5), 370), Color.Black);
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
                this.spriteBatch.DrawString(this.sf, sizeTeam.ToString(), new Vector2((int)(this.screen.Width - (150 / 1.5)), (int)(590 / 1.5)), Color.Black);
                this.spriteBatch.DrawString(this.sf, maxLvl.ToString(), new Vector2((int)(this.screen.Width - (100 / 1.5)), (int)(655 / 1.5)), Color.Black);
                this.spriteBatch.DrawString(this.sf, avgLvl.ToString(), new Vector2((int)(this.screen.Width - (100 / 1.5)), (int)(680 / 1.5)), Color.Black);

                int dec = 0;
                foreach (var item in this.lbc)
                {
                    this.spriteBatch.DrawString(this.sf_bc, item, new Vector2((int)(410 / 1.5), 425 + dec), Color.White);
                    dec += (int)(25 / 1.5);
                }

            }
            if (this.map.SquareDetailsOn)
            {
                System.Diagnostics.Debug.Assert(this.map.Inventory != null);
                this.map.SquareDetails.Draw(this.spriteBatch, new Microsoft.Xna.Framework.Rectangle(this.screen.Width - (int)(this.map.SquareDetails.getBounds().Width / 1.5), 0, (int)(this.map.SquareDetails.getBounds().Width / 1.5), (int)(this.map.SquareDetails.getBounds().Height / 1.5)));
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[0], new Vector2((int)(this.screen.Width - (80 / 1.5)), (int)(100 / 1.5)), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[1], new Vector2((int)(this.screen.Width - (80 / 1.5)), (int)(155 / 1.5)), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[2], new Vector2((int)(this.screen.Width - (80 / 1.5)), (int)(210 / 1.5)), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[3], new Vector2((int)(this.screen.Width - (80 / 1.5)), (int)(265 / 1.5)), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[4], new Vector2((int)(this.screen.Width - (80 / 1.5)), (int)(325 / 1.5)), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[5], new Vector2((int)(this.screen.Width - (80 / 1.5)), (int)(380 / 1.5)), Color.Black);
                this.spriteBatch.DrawString(this.sf, this.map.Inventory[6], new Vector2((int)(this.screen.Width - (80 / 1.5)), (int)(440 / 1.5)), Color.Black);
            }
            this.spriteBatch.End();
        }
    }
}
