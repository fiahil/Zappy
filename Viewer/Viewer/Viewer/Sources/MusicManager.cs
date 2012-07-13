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
        bool active;
        int curr;

        public MusicManager(ContentManager cm)
        {
            Random rand = new Random();

            this.cm = cm;
            this.playlist = new List<Song>();
            for (int i = 1; i < 6; ++i)
                this.playlist.Add(cm.Load<Song>("Music/track" + i));
            this.active = true;
            curr = rand.Next(0, 6);
        }

        public void Mute()
        {
            MediaPlayer.IsMuted = !MediaPlayer.IsMuted;
        }

        public void Update()
        {
            if (this.playlist != null && MediaPlayer.State != MediaState.Playing)
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
