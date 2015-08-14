using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Data;
using System.Data.SQLite;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Threading;

namespace MediaPlayer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        MediaLibrary _library;
        MediaController _controller;
        SongList _songList;
        DispatcherTimer timer;
        int tick = 0;

        bool _findingMusic;

        public MainWindow()
        {
            if (!File.Exists(MediaLibrary.GetInstance().ConnectionString))
            {
                SQLiteConnection.CreateFile(MediaLibrary.GetInstance().ConnectionString);
                _library = MediaLibrary.GetInstance();
                MediaLibrary.GetInstance().Initialize();
            }
            else
                _library = MediaLibrary.GetInstance();

            _controller = MediaController.GetInstance();

            InitializeComponent();

            GenerateSongList();

            timer = new DispatcherTimer();
            timer.Interval = new TimeSpan(0, 0, 1);
            timer.Tick += timer_Tick;
            timer.Start();
        }

        /// <summary>
        /// Handles the On_Click events for the file menu items, allows user to search for music
        /// to be added to the library either by an individual song, an entire folder, or an entire
        /// directory.
        /// Also allows for the MediaPlayer to exit
        /// </summary>
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            //Retrieves the selected MenuItem
            MenuItem item = (MenuItem)sender;

            //If the exit option was clicked, closes the program
            if (item.Name == "Exit")
            {
                Application.Current.Shutdown();
            }
            //If any of the music search options were clicked, and the MediaFinder is not already
            //adding music to the library
            else if (!_findingMusic)
            {
                //If the user seleted the folder search
                if (item.Name == "SearchFromFolder")
                {
                    var dialog = new System.Windows.Forms.FolderBrowserDialog();
                    System.Windows.Forms.DialogResult result = dialog.ShowDialog();

                    if (result.ToString() == "OK")
                        //Sends the selected path to the findMusic() function
                        findMusic(dialog.SelectedPath);
                }
                //If the user selected the file search
                else if (item.Name == "SearchForFile")
                {
                    var dialog = new System.Windows.Forms.OpenFileDialog();
                    dialog.DefaultExt = ".mp3";
                    dialog.Filter = "MP3 Files (*.mp3)|*.mp3|WMA Files (*.wma)|*.wma|All Files |*.mp3;*.wma";
                    dialog.Multiselect = false;
                    System.Windows.Forms.DialogResult result = dialog.ShowDialog();

                    if (result.ToString() == "OK")
                        //Sends the selected path to the findMusic() function
                        findMusic(dialog.FileName);
                }
            }
            //If the user wanted to search for music, but music is already being added to the library,
            //displays an error message box
            else
            {
                MessageBox.Show("Music is already being added, please wait before adding more.", "Add Music", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        /// <summary>
        /// If pathName is a directory, searches the directory for all valid audio files,
        /// likewise if pathName is a file, adds the given file(s) to the media library
        /// </summary>
        /// <param name="pathName"></param>
        private void findMusic(string pathName)
        {
            //Starts the DispatcherTimer used to update the "last song added" text
            _findingMusic = true;
            
            //Used to check if the given path is a file or directory
            FileAttributes fileAttribute = File.GetAttributes(pathName);

            //Creates the new thread that will add the given audio file(s) to the media library
            Task mytask = Task.Run(() =>
            {
                Thread.CurrentThread.IsBackground = true;

                if ((fileAttribute & FileAttributes.Directory) == FileAttributes.Directory)
                    MediaFinder.SearchForMedia(pathName);
                else
                    MediaFinder.AddMediaToLibrary(new List<string> { pathName });

                _findingMusic = false;
            });
        }
        /// <summary>
        /// On every tick of the DispatcherTimer, updates the current song being added text
        /// </summary>
        private void timer_Tick(object sender, object e)
        {
            tick++;

            CurrentSong.Text = _controller.NowPlaying;

            UpdatedCurrentSongBeingAdded(MediaLibrary.GetInstance().AddingSongs);
        }

        /// <summary>
        /// Updates the current song being added text, as well as stops the
        /// DispatcherTimer when the Media Library is done adding files
        /// </summary>
        /// <param name="final">Boolean value that says whether the files are still being added to the library</param>
        private void UpdatedCurrentSongBeingAdded(bool final)
        {
            if (MediaLibrary.GetInstance().MostRecentSong == "")
            {
                txtMusicFinder.Visibility = Visibility.Hidden;
                txtFileName.Visibility = Visibility.Hidden;
            } 
            else
            {
                txtFileName.Text = "Last song added: " + MediaLibrary.GetInstance().MostRecentSong;
                txtMusicFinder.Visibility = Visibility.Visible;
                txtFileName.Visibility = Visibility.Visible;

                if (final && tick % 10 == 0)
                    GenerateSongList();
            }
        }

        //Updates the song list
        private void GenerateSongList()
        {
            _songList = new SongList
            {
                HorizontalAlignment = HorizontalAlignment.Center,
                VerticalAlignment = VerticalAlignment.Center,
                Width = 900,
                Height = 604,
                Margin = new Thickness(0, 75, 0, 24)
            };

            MainGrid.Children.Add(_songList);
            LoadSongsToSongList();
        }

        /// <summary>
        /// Used in GenerateSongList, retrieves all the songs from the media library
        /// and then adds each one to the SongList control
        /// </summary>
        private void LoadSongsToSongList()
        {
            DataTable songTable = MediaLibrary.GetInstance().GetAllSongs();

            string title;
            string artist;
            string album;
            string genres;
            string plays;
            string rating;
            string id;

            foreach (DataRow row in songTable.Rows)
            {
                genres = "";

                title = row["SongTitle"].ToString();
                artist = row["ArtistName"].ToString();
                album = row["AlbumName"].ToString();
                plays = row["Plays"].ToString();
                rating = row["Rating"].ToString();
                id = row["ID"].ToString();

                DataTable genreTable = MediaLibrary.GetInstance().GetSongGenres(id);

                foreach (DataRow gRow in genreTable.Rows)
                {
                    genres = genres + gRow["Genre"].ToString();
                }

                _songList.AddSong(title, artist, album, genres, plays, rating, id);
            }
        }

        /// <summary>
        /// When the play button is clicked, plays the selected song(s)
        /// changes play button to pause button
        /// </summary>
        private void Play_Click(object sender, RoutedEventArgs e)
        {
            List<string> songsToPlay = new List<string>();

            foreach (Song song in _songList.lvSongListings.SelectedItems)
            {
                songsToPlay.Add(song.ID);
            }

            if (songsToPlay.Count != 0)
                _controller.AddMusicToUpNext(songsToPlay);

            _controller.PlayMusic();
            Play.Content = "pause";

            UnselectAllRows();
            Play.Click -= Play_Click;
            Play.Click += Pause_Click;
        }

        /// <summary>
        /// Pauses the playing music, changes pause button to play button
        /// </summary>
        private void Pause_Click(object sender, RoutedEventArgs e)
        {
            _controller.PauseMusic();
            Play.Content = "play";

            Play.Click += Play_Click;
            Play.Click -= Pause_Click;
        }

        /// <summary>
        /// Skips the currently playing song. If no other songs are in queue
        /// stops the music
        /// </summary>
        private void Skip_Click(object sender, RoutedEventArgs e)
        {
            _controller.SkipSong();
        }

        /// <summary>
        /// Stops all music from playing
        /// </summary>
        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            _controller.StopMusic();

            Play.Content = "play";

            Play.Click += Play_Click;
            Play.Click -= Pause_Click;
        }

        /// <summary>
        /// Unselects all the rows
        /// </summary>
        private void UnselectAllRows()
        {
            _songList.lvSongListings.SelectedItems.Clear();
        }
    }
}
