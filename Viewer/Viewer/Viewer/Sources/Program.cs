using System;

namespace Viewer.Sources
{
#if WINDOWS || XBOX
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            using (Main game = new Main())
            {
                try
                {
                    game.Run();
                }
                catch { }
            }
        }
    }
#endif
}

