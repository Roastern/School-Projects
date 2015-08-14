using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SQLite;
using System.Data;
using System.Windows.Forms;

namespace MediaPlayer
{
    public class MediaLibrary
    {
        //Maintains the locks on the current instance to ensure no other instances are created
        protected static WeakReference _instance = new WeakReference(null);
        protected static object _lock = new Object();

        //The name of the database file
        protected const string _connectionString = @"medialibrary.sqlite";
        public string ConnectionString
        { get { return _connectionString; } }

        //The connection
        protected SQLiteConnection _connection;
        protected SQLiteConnection _getSongInfo;
        protected SQLiteConnection _updateSongInfo;
        protected SQLiteConnection _generalRetrievalConnection;
        protected SQLiteConnection _genreRetrieverConnection;

        bool _addingSongs = false;
        public bool AddingSongs
        { get { return _addingSongs; } }

        private string _mostRecentSong;
        public string MostRecentSong
        { get { if (_addingSongs) return _mostRecentSong; else return ""; } }

        /// <summary>
        /// Sets up the database connection
        /// </summary>
        protected MediaLibrary()
        {
            _connection = new SQLiteConnection("Data Source=" + _connectionString + ";Version=3;");
            
            _generalRetrievalConnection = new SQLiteConnection("Data Source=" + _connectionString + ";Version=3;");

            _genreRetrieverConnection = new SQLiteConnection("Data Source=" + _connectionString + ";Version=3;");

            _getSongInfo = new SQLiteConnection("Data Source=" + _connectionString + ";Version=3;");

            _updateSongInfo = new SQLiteConnection("Data Source=" + _connectionString + ";Version=3;");
        }

        /// <summary>
        /// Returns the only instance of MediaLibrary
        /// </summary>
        public static MediaLibrary GetInstance()
        {
            MediaLibrary strongReference = (MediaLibrary)_instance.Target;
            if (strongReference == null)
            {
                lock (_lock)
                {
                    if (strongReference == null)
                    {
                        strongReference = new MediaLibrary();
                        _instance = new WeakReference(strongReference);
                    }
                }
            }

            return strongReference;
        }

        /// <summary>
        /// Creates the database tables
        /// </summary>
        public void Initialize()
        {
            _connection.Open();

            string tblSongGenre = @"CREATE TABLE SongGenre
                                    (
                                        SongID,
                                        GenreID,
                                        FOREIGN KEY (SongID) REFERENCES Song(SongID),
                                        FOREIGN KEY (GenreID) REFERENCES Genre(GenreID)
                                    );";

            string tblSong = @"CREATE TABLE Song 
                               (
                                    SongID INTEGER PRIMARY KEY, 
                                    Title varchar(500), 
                                    Path varchar(500),
                                    AlbumID int, 
                                    ArtistID int, 
                                    Track int,
                                    Plays int, 
                                    Rating int,
                                    FOREIGN KEY (AlbumID) REFERENCES Album(AlbumID),
                                    FOREIGN KEY (ArtistID) REFERENCES Artist(ArtistID)
                                );";

            string tblAlbum = @"CREATE TABLE Album 
                                (
                                    AlbumID INTEGER PRIMARY KEY, 
                                    Title varchar(500), 
                                    ArtistID int, 
                                    Artwork varchar(500),
                                    FOREIGN KEY (ArtistID) REFERENCES Artist(ArtistID)
                                );";

            string tblArtist = @"CREATE TABLE Artist
                                (
                                    ArtistID INTEGER PRIMARY KEY,
                                    Name varchar(500)
                                );";

            string tblGenre = @"CREATE TABLE Genre
                                (
                                    GenreID INTEGER PRIMARY KEY,
                                    Name varchar(500)
                                );";

            SQLiteCommand tableSetUp = new SQLiteCommand(tblGenre + "\n" + tblArtist + "\n" + tblAlbum + "\n" + tblSong + "\n" + tblSongGenre, _connection);

            tableSetUp.ExecuteNonQuery();

            _connection.Close();
        }

        /// <summary>
        /// Retrieves all songs currently in the database
        /// </summary>
        /// <returns>Returns a SQLDataReader object containing all the songs in the database</returns>
        public DataTable GetAllSongs()
        {
            _generalRetrievalConnection.Open();

            string retrievalString = @"SELECT Song.Title AS SongTitle, Artist.Name AS ArtistName, Album.Title AS AlbumName, Song.Plays AS Plays, Song.Rating AS Rating, Song.SongID AS ID
                                       FROM Song JOIN Artist
                                                    ON Song.ArtistID = Artist.ArtistID
                                                 JOIN Album
                                                    ON Song.AlbumID = Album.AlbumID
                                       ORDER BY Song.Title ASC;";

            SQLiteCommand retrieveSong = new SQLiteCommand(retrievalString, _generalRetrievalConnection);
            SQLiteDataReader datareader = retrieveSong.ExecuteReader();

            DataTable returnTable = new DataTable();
            returnTable.Load(datareader);

            _generalRetrievalConnection.Close();

            return returnTable;
        }

        /// <summary>
        /// Returns all the genres associated with the given song
        /// </summary>
        /// <param name="ID">The identifier for the song in the database</param>
        /// <returns>Returns a SQLDataReader object containing all the genres associated with the given song</returns>
        public DataTable GetSongGenres(string ID)
        {
            _genreRetrieverConnection.Open();

            string retrievalString = @"SELECT Genre.Name AS [Genre]
                                       FROM Genre JOIN SongGenre
                                                    ON Genre.GenreID = SongGenre.GenreID
                                                    AND SongGenre.SongID = @SongID;";

            SQLiteCommand retrieveGenres = new SQLiteCommand(retrievalString, _genreRetrieverConnection);
            retrieveGenres.Parameters.Add(new SQLiteParameter("@SongID", ID));

            SQLiteDataReader datareader = retrieveGenres.ExecuteReader();
            DataTable returnTable = new DataTable();
            returnTable.Load(datareader);

            _genreRetrieverConnection.Close();

            return returnTable;
        }

        /// <summary>
        /// Adds the given song and all of its relevant information to the database
        /// </summary>
        public void AddSongToLibrary(List<string[]> extendedSongList)
        {
            _addingSongs = true;

            _connection.Open();

            foreach (string[] collection in extendedSongList)
            {
                long artistID;
                long albumID;
                long songID = 0;
                int count;
                long genreID;

                string song = collection[0];
                string title = collection[1];
                string track = collection[2];
                string album = collection[3];
                string artist = collection[4];
                string genre = collection[5];

                _mostRecentSong = title;

                #region Artist Logic
                //Checks to see if the songs artist is already in the database
                string addArtist = @"SELECT count(*) FROM Artist WHERE Name = @ArtistName;";
                SQLiteParameter artistParam = new SQLiteParameter("@ArtistName", artist);
                SQLiteCommand artistexists = new SQLiteCommand(addArtist, _connection);
                artistexists.Parameters.Add(artistParam);

                count = Convert.ToInt32(artistexists.ExecuteScalar());

                //If the artist is not found, adds the artist
                if (count == 0)
                {
                    addArtist = @"INSERT INTO Artist (Name) VALUES (@ArtistName)";
                    artistexists = new SQLiteCommand(addArtist, _connection);
                    artistexists.Parameters.Add(artistParam);
                    artistexists.ExecuteNonQuery();

                    addArtist = @"SELECT last_insert_rowid();";
                    artistexists = new SQLiteCommand(addArtist, _connection);
                    artistID = (long)artistexists.ExecuteScalar();
                }
                //If the artist already exists, gets the artistID
                else
                {
                    addArtist = @"SELECT ArtistID FROM Artist WHERE Name = @ArtistName;";
                    artistexists = new SQLiteCommand(addArtist, _connection);
                    artistexists.Parameters.Add(artistParam);
                    artistID = (long)artistexists.ExecuteScalar();
                }
                #endregion

                #region Album logic
                //Checks to see if the songs album is already in the database
                string addAlbum = @"SELECT count(*) FROM Album WHERE Title = @AlbumName;";
                SQLiteParameter albumParam = new SQLiteParameter("@AlbumName", album);
                SQLiteParameter albumAParam = new SQLiteParameter("@ArtistID", artistID.ToString());
                SQLiteCommand albumexists = new SQLiteCommand(addAlbum, _connection);
                albumexists.Parameters.Add(albumParam);

                count = Convert.ToInt32(albumexists.ExecuteScalar());

                //If the album is not in the database, it is added
                if (count == 0)
                {
                    addAlbum = @"INSERT INTO Album (Title, ArtistID) VALUES (@AlbumName, @ArtistID);";
                    albumexists = new SQLiteCommand(addAlbum, _connection);
                    albumexists.Parameters.Add(albumParam);
                    albumexists.Parameters.Add(albumAParam);
                    albumexists.ExecuteNonQuery();

                    addAlbum = @"SELECT last_insert_rowid();";
                    albumexists = new SQLiteCommand(addAlbum, _connection);
                    albumexists.Parameters.Add(albumParam);
                    albumID = (long)albumexists.ExecuteScalar();
                }
                //If the album already exists, gets the album id
                else
                {
                    addAlbum = @"SELECT AlbumID FROM Album WHERE Title = @AlbumName;";
                    albumexists = new SQLiteCommand(addAlbum, _connection);
                    albumexists.Parameters.Add(albumParam);
                    albumID = (long)albumexists.ExecuteScalar();
                }
                #endregion

                #region Genre logic
                //Checks to see if all the songs genres are in the database
                string addGenre = @"SELECT count(*) FROM Genre WHERE Name = @GenreName;";
                SQLiteParameter genreParam = new SQLiteParameter("@GenreName", genre);
                SQLiteCommand genreexists = new SQLiteCommand(addGenre, _connection);
                genreexists.Parameters.Add(genreParam);

                count = Convert.ToInt32(genreexists.ExecuteScalar());

                //If the genre is not already in the database, adds it
                if (count == 0)
                {
                    addGenre = @"INSERT INTO Genre (Name) VALUES (@GenreName);";
                    genreexists = new SQLiteCommand(addGenre, _connection);
                    genreexists.Parameters.Add(genreParam);
                    genreexists.ExecuteNonQuery();

                    addGenre = @"SELECT last_insert_rowid();";
                    genreexists = new SQLiteCommand(addGenre, _connection);
                    genreexists.Parameters.Add(genreParam);
                    genreID = (long)genreexists.ExecuteScalar();
                }
                //Otherwise, gets the genre id
                else
                {
                    addGenre = @"SELECT GenreID FROM Genre WHERE Name = @GenreName;";
                    genreexists = new SQLiteCommand(addGenre, _connection);
                    genreexists.Parameters.Add(genreParam);
                    genreID = (long)genreexists.ExecuteScalar();
                }
                #endregion

                #region Song logic
                //Checks first to see if the filepath given is already in the database
                string addSong = @"SELECT count(*) FROM Song WHERE Path = @FilePath;";
                SQLiteParameter songParam = new SQLiteParameter("@SongName", title);
                SQLiteParameter songPath = new SQLiteParameter("@FilePath", song);
                SQLiteParameter songAParam = new SQLiteParameter("@AlbumID", albumID.ToString());
                SQLiteCommand songexists = new SQLiteCommand(addSong, _connection);
                songexists.Parameters.Add(songParam);
                songexists.Parameters.Add(songPath);
                songexists.Parameters.Add(albumAParam);
                songexists.Parameters.Add(songAParam);

                count = Convert.ToInt32(songexists.ExecuteScalar());

                //If it hasn't, adds the song
                if (count == 0)
                {
                    addSong = @"INSERT INTO Song (Title, Path, AlbumID, ArtistID, Track, Plays, Rating) VALUES (@SongName, @FilePath, @AlbumID, @ArtistID, " + track.ToString() + ", 0, 0);";
                    songexists = new SQLiteCommand(addSong, _connection);
                    songexists.Parameters.Add(songParam);
                    songexists.Parameters.Add(songPath);
                    songexists.Parameters.Add(albumAParam);
                    songexists.Parameters.Add(songAParam);
                    songexists.ExecuteNonQuery();

                    addSong = @"SELECT last_insert_rowid();";
                    songexists = new SQLiteCommand(addSong, _connection);
                    songID = (long)songexists.ExecuteScalar();
                }

                #endregion

                #region Song Genre logic
                //If the song was added, adds the genre for the song
                if (songID != 0)
                {
                    string addSongGenre = @"INSERT INTO SongGenre (SongID, GenreID) VALUES (@SongID, @GenreID);";
                    SQLiteParameter sID = new SQLiteParameter("@SongID", songID.ToString());
                    SQLiteParameter gID = new SQLiteParameter("@GenreID", genreID);
                    genreexists = new SQLiteCommand(addSongGenre, _connection);
                    genreexists.Parameters.Add(sID);
                    genreexists.Parameters.Add(gID);

                    genreexists.ExecuteNonQuery();
                }

                #endregion
            }

            _connection.Close();

            _addingSongs = false;
        }

        /// <summary>
        /// Gets the path of the song with the given ID
        /// </summary>
        /// <param name="ID">The ID of the song to be retrieved</param>
        public string GetSongPath(string ID)
        {
            _getSongInfo.Open();

            string getSongPath = "SELECT Path FROM Song WHERE SongID = @SongID;";
            SQLiteCommand getInfo = new SQLiteCommand(getSongPath, _getSongInfo);
            getInfo.Parameters.Add(new SQLiteParameter("@SongID", ID));

            string pathName = getInfo.ExecuteScalar().ToString();

            _getSongInfo.Close();

            return pathName;
        }

        /// <summary>
        /// Gets the title of the song with the given ID
        /// </summary>
        /// <param name="ID">The ID of the song to be retrieved</param>
        public string GetSongName(string ID)
        {
            _getSongInfo.Open();

            string getSongPath = "SELECT Title FROM Song WHERE SongID = @SongID;";
            SQLiteCommand getInfo = new SQLiteCommand(getSongPath, _getSongInfo);
            getInfo.Parameters.Add(new SQLiteParameter("@SongID", ID));

            string title = getInfo.ExecuteScalar().ToString();

            _getSongInfo.Close();

            return title;
        }

        /// <summary>
        /// Increments the play count by one
        /// </summary>
        /// <param name="ID">The SongID for the song whose play count is to be updated</param>
        public void UpdatePlayCount(string ID)
        {
            _updateSongInfo.Open();

            string updateSongInfo = "SELECT Plays FROM Song WHERE SongID = @SongID";
            SQLiteParameter idParam = new SQLiteParameter("@SongID", ID);
            SQLiteCommand updateCommand = new SQLiteCommand(updateSongInfo, _updateSongInfo);
            updateCommand.Parameters.Add(idParam);

            int playCount = Convert.ToInt32(updateCommand.ExecuteScalar());
            playCount++;

            updateSongInfo = "UPDATE Song SET Plays = @PlayCount WHERE SongID = @SongID";
            SQLiteParameter playParam = new SQLiteParameter("@PlayCount", playCount);
            updateCommand = new SQLiteCommand(updateSongInfo, _updateSongInfo);
            updateCommand.Parameters.Add(idParam);
            updateCommand.Parameters.Add(playParam);

            updateCommand.ExecuteNonQuery();

            _updateSongInfo.Close();
        }

        /// <summary>
        /// Updates the given song to have the given rating value
        /// </summary>
        /// <param name="ID">The ID of the song to be updated</param>
        /// <param name="rating">The rating to be associated with the given song</param>
        public void UpdateRating(string ID, string rating)
        {
            _updateSongInfo.Open();

            string updateSongInfo = "UPDATE Song SET Rating = @Rating WHERE SongID = @SongID";
            SQLiteParameter idParam = new SQLiteParameter("@SongID", ID);
            SQLiteParameter ratingParam = new SQLiteParameter("@Rating", rating);
            SQLiteCommand updateCommand = new SQLiteCommand(updateSongInfo, _updateSongInfo);
            updateCommand.Parameters.Add(idParam);
            updateCommand.Parameters.Add(ratingParam);

            updateCommand.ExecuteNonQuery();

            _updateSongInfo.Close();
        }
    }
}
