using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

namespace MediaPlayer
{
    /// <summary>
    /// Interaction logic for SongList.xaml
    /// </summary>
    public partial class SongList : UserControl
    {
        protected List<Song> songs;

        public SongList()
        {
            songs = new List<Song>();

            InitializeComponent();

            string[] m0 = { Convert.ToInt16(RatingList._0).ToString(), Convert.ToInt16(RatingList._1).ToString(), Convert.ToInt16(RatingList._2).ToString(), Convert.ToInt16(RatingList._3).ToString(), Convert.ToInt16(RatingList._4).ToString(), Convert.ToInt16(RatingList._5).ToString() };
            dgCB.ItemsSource = m0;

            lvSongListings.ItemsSource = songs;
        }

        public void AddSong(string title, string artist, string album, string genres, string plays, string rating, string id)
        {
            songs.Add(new Song() { Title = title, Artist = artist, Album = album, Genre = genres, Plays = plays, Rating = rating, ID = id });
        }

        private void Grid_MouseEnter(object sender, MouseEventArgs e)
        {
            Grid thisGrid = (Grid)sender;
            thisGrid.Background = Brushes.Gainsboro;
        }

        private void Grid_MouseLeave(object sender, MouseEventArgs e)
        {
            Grid thisGrid = (Grid)sender;
            thisGrid.Background = Brushes.Transparent;
        }

        private void OnSelectionChange(object sender, SelectionChangedEventArgs e)
        {
            ComboBox ratingBox = (ComboBox)sender;
            Song selectedSong = (Song)lvSongListings.SelectedItem;

            if (ratingBox.SelectedValue != null)
            {
                string rating = ratingBox.SelectedValue.ToString();

                MediaLibrary.GetInstance().UpdateRating(selectedSong.ID, rating);
            }
        }
    }

    public enum RatingList { _0 = 0, _1 = 1, _2 = 2, _3 = 3, _4 = 4, _5 = 5 };

    public class Song
    {
        public string Title
        { get; set; }

        public string Artist
        { get; set; }

        public string Album
        { get; set; }

        public string Genre
        { get; set; }

        public string Plays
        { get; set; }

        public string Rating
        { get; set; }

        public string ID
        { get; set; }
    }
}
