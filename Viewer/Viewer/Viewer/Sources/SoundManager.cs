using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Media;

namespace Viewer.Sources
{
    public class SoundManager
    {
        Dictionary<string, SoundEffect> soundbank;
        ContentManager cm;
        bool play;

        public SoundManager(ContentManager cmo)
        {
            play = true;
            this.cm = cmo;
            soundbank = new Dictionary<string, SoundEffect>();
            soundbank["pbc"] = cm.Load<SoundEffect>("Sounds/Broadcast");
            soundbank["pdi"] = cm.Load<SoundEffect>("Sounds/Dead");
            soundbank["pdr"] = cm.Load<SoundEffect>("Sounds/Drop");
            soundbank["pex"] = cm.Load<SoundEffect>("Sounds/Expulse");
            soundbank["pfk"] = cm.Load<SoundEffect>("Sounds/Fork");
            soundbank["pgt"] = cm.Load<SoundEffect>("Sounds/Take");
            soundbank["pic"] = cm.Load<SoundEffect>("Sounds/Incantation");
            soundbank["ppo"] = cm.Load<SoundEffect>("Sounds/Move");
            soundbank["plv"] = cm.Load<SoundEffect>("Sounds/Up");
        }

        public void Mute()
        {
            this.play = !this.play;
        }

        public void PlaySound(string snd)
        {
            if (play)
                soundbank[snd].Play();
        }
    }
}
