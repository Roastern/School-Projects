using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace MediaPlayer
{
    class MediaController
    {
        //Maintains the locks on the current instance to ensure no other instances are created
        protected static WeakReference _instance = new WeakReference(null);
        protected static object _lock = new Object();

        //Maintains a list of songs that will be played in the order they were added
        List<string> _upNext;
        public List<string> UpNext
        { get { return _upNext; } }

        private string _nowPlayingID;

        //Maintains the current song that is being played
        string _nowPlaying;
        public string NowPlaying
        { get { return _nowPlaying; } }

        System.Windows.Media.MediaPlayer player;

        /// <summary>
        /// Sets up the database connection
        /// </summary>
        protected MediaController()
        {
            player = new System.Windows.Media.MediaPlayer();
            player.MediaEnded += OnSongEnd;

            _upNext = new List<string>();
        }

        /// <summary>
        /// Returns the only instance of MediaController
        /// </summary>
        public static MediaController GetInstance()
        {
            MediaController strongReference = (MediaController)_instance.Target;
            if (strongReference == null)
            {
                lock (_lock)
                {
                    if (strongReference == null)
                    {
                        strongReference = new MediaController();
                        _instance = new WeakReference(strongReference);
                    }
                }
            }

            return strongReference;
        }

        /// <summary>
        /// Adds the given list of strings to the list of songs that will be played
        /// </summary>
        /// <param name="songList">The list of songs to be added to "Up Next"</param>
        public void AddMusicToUpNext(List<string> songList)
        {
            DialogResult choice;

            //If there are already songs in the up next queue, prompts the user on whether they
            //would like to replace the songs in queue, or add the new songs to the end of the queue
            if (UpNext.Count != 0)
            {
                choice = MessageBox.Show("There are already songs in queue, would you like to add the music to the end of the queue?", "Add songs to up next queue", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);

                if (choice == DialogResult.Yes)
                    _upNext.AddRange(songList);
                else
                {
                    _upNext = songList;
                    player.Close();
                    PlayMusic();
                }
            }
            //If there are no songs in the up next queue, just adds the new list
            //of songs to the queue
            else
            {
                _upNext = songList;
                player.Close();
                PlayMusic();
            }
        }

        /// <summary>
        /// Plays the song currently up next, resumes playing if paused
        /// </summary>
        public void PlayMusic()
        {
            if (player.Source != null)
                player.Play();
            else
            {
                if (_upNext.Count != 0)
                {
                    _nowPlayingID = _upNext[0];
                    _upNext.RemoveAt(0);

                    _nowPlaying = MediaLibrary.GetInstance().GetSongName(_nowPlayingID);
                    MediaLibrary.GetInstance().UpdatePlayCount(_nowPlayingID);

                    Uri uri = new Uri(MediaLibrary.GetInstance().GetSongPath(_nowPlayingID));

                    player.Open(uri);
                    player.Play();
                }
            }
        }

        /// <summary>
        /// Pauses the player if a song is being played
        /// </summary>
        public void PauseMusic()
        {
            player.Pause();
        }

        /// <summary>
        /// Stops the current song from playing
        /// </summary>
        public void StopMusic()
        {
            player.Stop();
        }

        /// <summary>
        /// Skips to the next song in the up next list, if one exists
        /// </summary>
        public void SkipSong()
        {
            if (_upNext.Count != 0)
            {
                _nowPlayingID = _upNext[0];
                _upNext.RemoveAt(0);

                _nowPlaying = MediaLibrary.GetInstance().GetSongName(_nowPlayingID);

                Uri uri = new Uri(MediaLibrary.GetInstance().GetSongPath(_nowPlayingID));

                player.Open(uri);
                player.Play();
            }
        }

        /// <summary>
        /// Event handler used to play the next song in the up next queue when the current song ends
        /// </summary>
        private void OnSongEnd(object sender, object e)
        {
            if (_upNext.Count != 0)
            {
                _nowPlayingID = _upNext[0];
                _upNext.RemoveAt(0);

                _nowPlaying = MediaLibrary.GetInstance().GetSongName(_nowPlayingID);

                Uri uri = new Uri(MediaLibrary.GetInstance().GetSongPath(_nowPlayingID));

                player.Open(uri);
                player.Play();
            }
        }
    }
}
