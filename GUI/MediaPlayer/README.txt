Media Player was a pretty basic assignment: 

Use WPF to play or present some form of media. Bonus points for using a database for keeping track of the media.

So I decided to make my own music player, with SQLite storing the locations of music files, as well as other basic information such as number of plays, rating, album (I used a normalized database structure to keep track of all the songs in albums, etc).
I also used this project as an opportunity to explore multithreading. 
Although it is fully functional, there is still a lot of work to be done on it (I'm looking at you, UI). 

If/when I get free time, I plan to revisit and update this project.

taglib-sharp was used to pull the data from the music files, you can take a look at it here:
https://github.com/mono/taglib-sharp