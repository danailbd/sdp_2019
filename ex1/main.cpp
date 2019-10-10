#include <iostream>
#include <cstring>

class Time
{
public:
    Time (int secs, int mins=0, int hours=0)
        : m_seconds(secs),
          m_minutes(mins),
          m_hours(hours)
    {}

    int seconds() const {
        return m_seconds;
    }

    int minutes() const {
        return m_minutes;
    }

    int hours() const {
        return m_hours;
    }

private:
    short m_seconds,
          m_minutes,
          m_hours;
};

class Song
{
public:
    Song (std::string title, std::string author, Time duration)
        : m_title(title),
          m_author(author),
          m_duration(duration)
    {}
    virtual ~Song () {}; // just in case

    std::string title() const {
        return m_title;
    }

    std::string author() const {
        return m_author;
    }

    Time duration() const {
        return m_duration;
    }

private:
    std::string m_title;
    std::string m_author;
    Time m_duration;
};


class Spotify
{
public:
    Spotify (Song songsSource[]) {
        // TODO real world scenario we'd be using
        // a service here, e.g. database. It should be
        // conceptionally the same
        
    };

    virtual ~Spotify () {
        delete [] m_songsDatabase;
    };

    const Song* findByTitle (std::string songTitle) {
        for (int i = 0; i < m_songsDatabaseSize; i++) {
            if (m_songsDatabase[i].title() == songTitle) {
                return m_songsDatabase + i;
            }
        }

        return nullptr;
    }

private:
    Song* m_songsDatabase;
    int m_songsDatabaseSize;
};

// TODO tests
// TODO write down the new ideas

int main()
{
    Song songsSource[] = { Song(std::string("Hurt"), std::string("Johnny Cash"), Time(10, 3)) };
    Spotify mySpotify(songsSource);

    const Song* x = mySpotify.findByTitle("Hurt");

    std::cout << "Hello" << std::endl;
    std::cout << (x != nullptr ? x->title() : "No found") << std::endl;

    return 0;
}
