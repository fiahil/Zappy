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
    public class Elt
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

        Sprite marker;

        int off;
        Point p;

        bool selected;
        Inventory Iv;
        Rectangle Bounds;
        
        public bool Selected
        {
            get { return selected; }
            set { selected = value; }
        }

        public Inventory Inventory
        {
            get { return Iv; }
        }

        static Random rd = new Random();

        public Elt(SpriteBatch sb, Point p)
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
            this.p = p;
            this.off = rd.Next(3);

            this.Iv = new Inventory();

            this.selected = false;
        }

        public bool isInPolygon(Vector2 p, Rectangle square, Map map)
        {
            Vector2 pos = new Vector2(-(this.p.Y - 1) * (square.Width / 2) + square.X + ((this.p.X - 2) * (square.Width / 2)) + (map.getSize().Y) * (square.Width / 2),
                                      (this.p.Y - 1) * (square.Height / 2) + square.Y + ((this.p.X - 2) * (square.Height / 2)) - (map.getSize().Y) * (square.Height / 2));
            Polygon target = new Polygon(new Vector2[]
                {
                    new Vector2((square.X + pos.X) + square.Width / 2, (square.Y + pos.Y)),
                    new Vector2((square.X + pos.X) + square.Width, (square.Y + pos.Y) + square.Height / 2),
                    new Vector2((square.X + pos.X) + square.Width / 2, (square.Y + pos.Y) + square.Height),
                    new Vector2((square.X + pos.X), (square.Y + pos.Y) + square.Height / 2)
                });
            return target.Contains(p);
        }

        public void Load(SpriteManager cm)
        {
            this.tiles[0] = cm.GetSprite("Tiles/base1");
            this.tiles[1] = cm.GetSprite("Tiles/base2");
            this.tiles[2] = cm.GetSprite("Tiles/base3");

            this.nourriture[0] = cm.GetSprite("Resources/nourriture_small");
            this.nourriture[1] = cm.GetSprite("Resources/nourriture_big");

            this.linemate[0] = cm.GetSprite("Resources/linemate_small");
            this.linemate[1] = cm.GetSprite("Resources/linemate_big");

            this.deraumere[0] = cm.GetSprite("Resources/deraumere_small");
            this.deraumere[1] = cm.GetSprite("Resources/deraumere_big");

            this.sibur[0] = cm.GetSprite("Resources/sibur_small");
            this.sibur[1] = cm.GetSprite("Resources/sibur_big");

            this.mendiane[0] = cm.GetSprite("Resources/mendiane_small");
            this.mendiane[1] = cm.GetSprite("Resources/mendiane_big");

            this.phiras[0] = cm.GetSprite("Resources/phiras_small");
            this.phiras[1] = cm.GetSprite("Resources/phiras_big");

            this.thystame[0] = cm.GetSprite("Resources/thystame_small");
            this.thystame[1] = cm.GetSprite("Resources/thystame_big");

            this.marker = cm.GetSprite("Tiles/base_highlited");

            this.Bounds = tiles[0].getBounds();
        }

        public void Draw(Rectangle square)
        {
            this.tiles[this.off].Draw(sb, square);

            if (this.Iv.nourriture > 0 && this.Iv.nourriture < 5)
                this.nourriture[0].Draw(sb, new Rectangle(square.X + (int)(98 * (square.Width / 155.0)), square.Y + (int)(18 * (square.Height / 58.0)), (int)(54.0 * (square.Width / 155.0 * 0.45)), (int)(48.0 * (square.Height / 58.0 * 0.45))));
            if (this.Iv.nourriture >= 5)
                this.nourriture[1].Draw(sb, new Rectangle(square.X + (int)(98 * (square.Width / 155.0)), square.Y + (int)(16 * (square.Height / 58.0)), (int)(66.0 * (square.Width / 155.0 * 0.45)), (int)(54.0 * (square.Height / 58.0 * 0.45))));

            if (this.Iv.mendiane > 0 && this.Iv.mendiane < 5)
                this.mendiane[0].Draw(sb, new Rectangle(square.X + (int)(41 * (square.Width / 155.0)), square.Y + (int)(8 * (square.Height / 58.0)), (int)(57.0 * (square.Width / 155.0 * 0.45)), (int)(50.0 * (square.Height / 58.0 * 0.45))));
            if (this.Iv.mendiane >= 5)
                this.mendiane[1].Draw(sb, new Rectangle(square.X + (int)(45 * (square.Width / 155.0)), square.Y + (int)(9 * (square.Height / 58.0)), (int)(66.0 * (square.Width / 155.0 * 0.45)), (int)(52.0 * (square.Height / 58.0 * 0.45))));

            if (this.Iv.phiras > 0 && this.Iv.phiras < 5)
                this.phiras[0].Draw(sb, new Rectangle(square.X + (int)(62 * (square.Width / 155.0)), square.Y + (int)(18 * (square.Height / 58.0)), (int)(54.0 * (square.Width / 155.0 * 0.45)), (int)(46.0 * (square.Height / 58.0 * 0.45))));
            if (this.Iv.phiras >= 5)
                this.phiras[1].Draw(sb, new Rectangle(square.X + (int)(62 * (square.Width / 155.0)), square.Y + (int)(15 * (square.Height / 58.0)), (int)(67.0 * (square.Width / 155.0 * 0.45)), (int)(53.0 * (square.Height / 58.0 * 0.45))));

            if (this.Iv.thystame > 0 && this.Iv.thystame < 5)
                this.thystame[0].Draw(sb, new Rectangle(square.X + (int)(80 * (square.Width / 155.0)), square.Y + (int)(25 * (square.Height / 58.0)), (int)(57.0 * (square.Width / 155.0 * 0.45)), (int)(51.0 * (square.Height / 58.0 * 0.45))));
            if (this.Iv.thystame >= 5)
                this.thystame[1].Draw(sb, new Rectangle(square.X + (int)(80 * (square.Width / 155.0)), square.Y + (int)(24 * (square.Height / 58.0)), (int)(66.0 * (square.Width / 155.0 * 0.45)), (int)(53.0 * (square.Height / 58.0 * 0.45))));

            if (this.Iv.linemate > 0 && this.Iv.linemate < 5)
                this.linemate[0].Draw(sb, new Rectangle(square.X + (int)(20 * (square.Width / 155.0)), square.Y + (int)(16 * (square.Height / 58.0)), (int)(62.0 * (square.Width / 155.0 * 0.45)), (int)(55.0 * (square.Height / 58.0 * 0.45))));
            if (this.Iv.linemate >= 5)
                this.linemate[1].Draw(sb, new Rectangle(square.X + (int)(22 * (square.Width / 155.0)), square.Y + (int)(17 * (square.Height / 58.0)), (int)(66.0 * (square.Width / 155.0 * 0.45)), (int)(53.0 * (square.Height / 58.0 * 0.45))));

            if (this.Iv.deraumere > 0 && this.Iv.deraumere < 5)
                this.deraumere[0].Draw(sb, new Rectangle(square.X + (int)(42 * (square.Width / 155.0)), square.Y + (int)(28 * (square.Height / 58.0)), (int)(55.0 * (square.Width / 155.0 * 0.45)), (int)(45.0 * (square.Height / 58.0 * 0.45))));
            if (this.Iv.deraumere >= 5)
                this.deraumere[1].Draw(sb, new Rectangle(square.X + (int)(40 * (square.Width / 155.0)), square.Y + (int)(22 * (square.Height / 58.0)), (int)(67.0 * (square.Width / 155.0 * 0.45)), (int)(58.0 * (square.Height / 58.0 * 0.45))));

            if (this.Iv.sibur > 0 && this.Iv.sibur < 5)
                this.sibur[0].Draw(sb, new Rectangle(square.X + (int)(64 * (square.Width / 155.0)), square.Y + (int)(36 * (square.Height / 58.0)), (int)(55.0 * (square.Width / 155.0 * 0.45)), (int)(43.0 * (square.Height / 58.0 * 0.45))));
            if (this.Iv.sibur >= 5)
                this.sibur[1].Draw(sb, new Rectangle(square.X + (int)(57 * (square.Width / 155.0)), square.Y + (int)(25 * (square.Height / 58.0)), (int)(72.0 * (square.Width / 155.0 * 0.45)), (int)(67.0 * (square.Height / 58.0 * 0.45))));

            if (this.selected)
            {
                this.marker.Draw(sb, square);
            }
        }
    }
}
