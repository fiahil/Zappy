using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Media;

namespace Viewer.Sources
{
    class MusicManager
    {
        ContentManager cm;
        List<Song> playlist;
        Song ending;
        bool active;
        bool play;
        int curr;

        public MusicManager(ContentManager cmo)
        {
            Random rand = new Random();

            this.cm = cmo;
            this.playlist = new List<Song>();
            for (int i = 1; i < 6; ++i)
                this.playlist.Add(cm.Load<Song>("Music/track" + i));
            this.ending = cm.Load<Song>("Music/Cantina");
            this.active = true;
            this.play = true;
            MediaPlayer.Volume = 0.5f;
            curr = rand.Next(0, 6);
        }

        public bool Play
        {
            get { return this.play; }
            set { this.play = value; }
        }

        public void Mute()
        {
            MediaPlayer.IsMuted = !MediaPlayer.IsMuted;
        }

        public void PlayEnd()
        {
            if (this.play)
            {
                this.play = false;
                MediaPlayer.Play(this.ending);
                MediaPlayer.IsRepeating = true;
            }
        }

        public void Update()
        {
            if (this.play && this.playlist != null && MediaPlayer.State != MediaState.Playing)
            {
                if (active)
                {
                    active = false;
                    if (++curr > this.playlist.Count - 1)
                        curr = 0;
                }
                MediaPlayer.Play(playlist[curr]);
            }
            if (MediaPlayer.State == MediaState.Playing)
                active = true;
        }
    }
}
