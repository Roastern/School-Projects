using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using TagLib;

namespace MediaPlayer
{
    static public class MediaFinder
    {
        static public void SearchForMedia()
        {

        }

        /// <summary>
        /// Searches for valid media at the given path and in all subdirectories within that path
        /// </summary>
        /// <param name="fileName">The directory to search for valid media files</param>
        static public void SearchForMedia(string fileName)
        {
            string[] songListWMA = Directory.GetFiles(fileName, "*.mp3", SearchOption.AllDirectories);
            string[] songListMP3 = Directory.GetFiles(fileName, "*.wma", SearchOption.AllDirectories);

            List<string> songList = new List<string>();

            songList.AddRange(songListWMA);
            songList.AddRange(songListMP3);

            AddMediaToLibrary(songList);
        }

        /// <summary>
        /// Adds the media at the given location to the database
        /// </summary>
        /// <param name="song">The filepaths of the media to be added to the database</param>
        static public void AddMediaToLibrary(List<string> songList)
        {
            string album;
            string artist;
            string title;
            string genre;
            string track;
            List<string[]> songExtendedList = new List<string[]>();
            
            foreach (String song in songList)
            {
                try
                {
                    TagLib.File mp3 = TagLib.File.Create(song);

                    //Creates the album string
                    if (mp3.Tag.Album != null && !String.IsNullOrEmpty(mp3.Tag.Album))
                        album = mp3.Tag.Album;
                    else
                        album = "";

                    //Creates the artist string
                    if (mp3.Tag.AlbumArtists.Length != 0)
                        artist = mp3.Tag.AlbumArtists[0];
                    else
                        artist = "";

                    //Creates the song title string
                    if (mp3.Tag.Title != null && !String.IsNullOrEmpty(mp3.Tag.Title))
                        title = mp3.Tag.Title;
                    else
                        title = "";

                    //Creates the list of genre strings
                    if (mp3.Tag.Genres.Length != 0)
                        genre = mp3.Tag.Genres[0];
                    else
                        genre = "";

                    //Creates the track value
                    track = mp3.Tag.Track.ToString();

                    string[] collection = { song, title, track, album, artist, genre };

                    songExtendedList.Add(collection);
                }
                catch
                {
                    Console.WriteLine(song);
                }
            }

            MediaLibrary.GetInstance().AddSongToLibrary(songExtendedList);
        }
    }
}
