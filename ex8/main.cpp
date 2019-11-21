#include <vector>
#include <cstring>
#include "../ex5/spotify.cpp"
#include "../lib/testing-framework.h"


void testPlaylistFlow() {

    std::vector<Song> testSongsDb = {
        Song("Why not", "Jimmy", Duration(150)),
        Song("Oh John", "Jack", Duration(150))
    };

    Spotify spotify(testSongsDb);



    const Song* song = spotify.findByTitle("Why not");

    UnitTests::AssertEq<std::string>("Why not", song->title(), "There is a found song");

    spotify.creatPlaylist("My list");
    spotify.addToPlaylist("My list", song);
}


int main()
{
    testPlaylistFlow();

    return 0;
}
