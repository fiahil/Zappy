using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Viewer.Sources
{
    public class SpriteManager
    {
        Dictionary<string, Sprite> db;

        public SpriteManager(ContentManager cm)
        {
            db = new Dictionary<string, Sprite>();

            this.db["Background/border"] = new Sprite(cm.Load<Texture2D>("Background/border"));
            this.db["Background/border2"] = new Sprite(cm.Load<Texture2D>("Background/border2"));
            this.db["Background/cloud"] = new Sprite(cm.Load<Texture2D>("Background/cloud"));
            this.db["Background/corner"] = new Sprite(cm.Load<Texture2D>("Background/corner"));
            this.db["Background/top_border"] = new Sprite(cm.Load<Texture2D>("Background/top_border"));
            this.db["Background/top_border2"] = new Sprite(cm.Load<Texture2D>("Background/top_border2"));
            this.db["Background/wall"] = new Sprite(cm.Load<Texture2D>("Background/wall"));
            this.db["Background/wall2"] = new Sprite(cm.Load<Texture2D>("Background/wall2"));
            this.db["Background/wall3"] = new Sprite(cm.Load<Texture2D>("Background/wall3"));

            this.db["Level/level_1"] = new Sprite(cm.Load<Texture2D>("Level/level_1"));
            this.db["Level/level_2"] = new Sprite(cm.Load<Texture2D>("Level/level_2"));
            this.db["Level/level_3"] = new Sprite(cm.Load<Texture2D>("Level/level_3"));
            this.db["Level/level_4"] = new Sprite(cm.Load<Texture2D>("Level/level_4"));
            this.db["Level/level_5"] = new Sprite(cm.Load<Texture2D>("Level/level_5"));
            this.db["Level/level_6"] = new Sprite(cm.Load<Texture2D>("Level/level_6"));
            this.db["Level/level_7"] = new Sprite(cm.Load<Texture2D>("Level/level_7"));
            this.db["Level/level_8"] = new Sprite(cm.Load<Texture2D>("Level/level_8"));

            this.db["Resources/deraumere_small"] = new Sprite(cm.Load<Texture2D>("Resources/deraumere_small"));
            this.db["Resources/deraumere_big"] = new Sprite(cm.Load<Texture2D>("Resources/deraumere_big"));

            this.db["Resources/linemate_small"] = new Sprite(cm.Load<Texture2D>("Resources/linemate_small"));
            this.db["Resources/linemate_big"] = new Sprite(cm.Load<Texture2D>("Resources/linemate_big"));

            this.db["Resources/mendiane_small"] = new Sprite(cm.Load<Texture2D>("Resources/mendiane_small"));
            this.db["Resources/mendiane_big"] = new Sprite(cm.Load<Texture2D>("Resources/mendiane_big"));

            this.db["Resources/nourriture_small"] = new Sprite(cm.Load<Texture2D>("Resources/nourriture_small"));
            this.db["Resources/nourriture_big"] = new Sprite(cm.Load<Texture2D>("Resources/nourriture_big"));

            this.db["Resources/phiras_small"] = new Sprite(cm.Load<Texture2D>("Resources/phiras_small"));
            this.db["Resources/phiras_big"] = new Sprite(cm.Load<Texture2D>("Resources/phiras_big"));

            this.db["Resources/sibur_small"] = new Sprite(cm.Load<Texture2D>("Resources/sibur_small"));
            this.db["Resources/sibur_big"] = new Sprite(cm.Load<Texture2D>("Resources/sibur_big"));

            this.db["Resources/thystame_small"] = new Sprite(cm.Load<Texture2D>("Resources/thystame_small"));
            this.db["Resources/thystame_big"] = new Sprite(cm.Load<Texture2D>("Resources/thystame_big"));

            this.db["Tiles/base_highlited"] = new Sprite(cm.Load<Texture2D>("Tiles/base_highlited"));
            this.db["Tiles/base1"] = new Sprite(cm.Load<Texture2D>("Tiles/base1"));
            this.db["Tiles/base2"] = new Sprite(cm.Load<Texture2D>("Tiles/base2"));
            this.db["Tiles/base3"] = new Sprite(cm.Load<Texture2D>("Tiles/base3"));
            this.db["Tiles/map_inventory"] = new Sprite(cm.Load<Texture2D>("Tiles/map_inventory"));
            this.db["Tiles/map_resources"] = new Sprite(cm.Load<Texture2D>("Tiles/map_resources"));
            this.db["Tiles/team_detail"] = new Sprite(cm.Load<Texture2D>("Tiles/team_detail"));
            this.db["Tiles/bc_box"] = new Sprite(cm.Load<Texture2D>("Tiles/bc_box"));

            this.db["Players/BL"] = new Sprite(cm.Load<Texture2D>("Players/BL"));
            this.db["Players/BL_2"] = new Sprite(cm.Load<Texture2D>("Players/BL_2"));

            this.db["Players/BL_fork"] = new Sprite(cm.Load<Texture2D>("Players/BL_fork"));
            this.db["Players/BL_fork_2"] = new Sprite(cm.Load<Texture2D>("Players/BL_fork_2"));

            this.db["Players/BL_prend"] = new Sprite(cm.Load<Texture2D>("Players/BL_prend"));
            this.db["Players/BL_prend_2"] = new Sprite(cm.Load<Texture2D>("Players/BL_prend_2"));

            this.db["Players/BR"] = new Sprite(cm.Load<Texture2D>("Players/BR"));
            this.db["Players/BR_2"] = new Sprite(cm.Load<Texture2D>("Players/BR_2"));

            this.db["Players/BR_fork"] = new Sprite(cm.Load<Texture2D>("Players/BR_fork"));
            this.db["Players/BR_fork_2"] = new Sprite(cm.Load<Texture2D>("Players/BR_fork_2"));

            this.db["Players/BR_prend"] = new Sprite(cm.Load<Texture2D>("Players/BR_prend"));
            this.db["Players/BR_prend_2"] = new Sprite(cm.Load<Texture2D>("Players/BR_prend_2"));

            this.db["Players/FL"] = new Sprite(cm.Load<Texture2D>("Players/FL"));
            this.db["Players/FL_2"] = new Sprite(cm.Load<Texture2D>("Players/FL_2"));

            this.db["Players/FL_fork"] = new Sprite(cm.Load<Texture2D>("Players/FL_fork"));
            this.db["Players/FL_fork_2"] = new Sprite(cm.Load<Texture2D>("Players/FL_fork_2"));

            this.db["Players/FL_prend"] = new Sprite(cm.Load<Texture2D>("Players/FL_prend"));
            this.db["Players/FL_prend_2"] = new Sprite(cm.Load<Texture2D>("Players/FL_prend_2"));

            this.db["Players/FR"] = new Sprite(cm.Load<Texture2D>("Players/FR"));
            this.db["Players/FR_2"] = new Sprite(cm.Load<Texture2D>("Players/FR_2"));

            this.db["Players/FR_fork"] = new Sprite(cm.Load<Texture2D>("Players/FR_fork"));
            this.db["Players/FR_fork_2"] = new Sprite(cm.Load<Texture2D>("Players/FR_fork_2"));

            this.db["Players/FR_prend"] = new Sprite(cm.Load<Texture2D>("Players/FR_prend"));
            this.db["Players/FR_prend_2"] = new Sprite(cm.Load<Texture2D>("Players/FR_prend_2"));

            this.db["Players/BroadcastL"] = new Sprite(cm.Load<Texture2D>("Players/BroadcastL"));
            this.db["Players/BroadcastR"] = new Sprite(cm.Load<Texture2D>("Players/BroadcastR"));
            this.db["Players/dead"] = new Sprite(cm.Load<Texture2D>("Players/dead"));
            this.db["Players/Egg"] = new Sprite(cm.Load<Texture2D>("Players/Egg"));
            this.db["Players/incant"] = new Sprite(cm.Load<Texture2D>("Players/incant"));
            this.db["Players/incant_2"] = new Sprite(cm.Load<Texture2D>("Players/incant_2"));
        }
        public Sprite GetSprite(string path)
        {
            return db[path];
        }
    }
}
