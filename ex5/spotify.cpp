#include <iostream>
#include <cstring>
#include <vector>


class Duration
{
public:
    Duration (int seconds)
        : m_seconds(seconds)
    {}

    int seconds() const {
        return m_seconds;
    }

private:
    short m_seconds;
};

class Song
{
public:
    Song (std::string title, std::string author, Duration duration)
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

    Duration duration() const {
        return m_duration;
    }

private:
    std::string m_title;
    std::string m_author;
    Duration m_duration;
};


class LQueue
{
public:
    LQueue ()
        : m_front(nullptr),
        m_back(nullptr)
    {}
    virtual ~LQueue ()
    {
        deleteRec(m_front);
    }

    void push(Song* song) {
        Node* newNode = new Node(song);

        if (m_back) {
            m_back->m_next = newNode;
            m_back = newNode;
        } else {
            m_front = m_back = newNode;
        }
    }

    void pop() {
        if (m_front == m_back)
            m_back = nullptr;

        Node* oldNode = m_front;
        m_front = m_front->m_next;
        delete oldNode;
    };

    Song* head() {
        return m_front ? m_front->m_value : nullptr;
    }

    bool empty()
    {
        return !m_front;
    }

protected:
    struct Node {
        Song* m_value;
        Node* m_next;

        Node(Song* val, Node* next = nullptr)
            : m_value(val),
            m_next(next)
        {}
    };

protected:
    void deleteRec (Node* root) {
        if (!root) return;

        deleteRec(root->m_next);
        delete root;
    } 


    Node* m_front,
        * m_back;
};

// TODO
class LDeque: public LQueue {};


class Player
{
public:
    Player () {};
    virtual ~Player () {};

    void play();
    void playNext();
    void playPrevious();

    void enqueueSong(Song* song);
    std::vector<Song*> getSongsQueue() const;

private:
    Song** m_queue;
};


/**********************************************************************
*                       Spotify main component                       *
**********************************************************************/


class Spotify
{
public:
    Spotify (std::vector<Song>& songsSource) {
        // TODO real world scenario we'd be using
        // a service here, e.g. database. It should be
        // conceptionally the same

        m_songsDatabase = songsSource;
    };

    virtual ~Spotify () {
    };

    const Song* findByTitle (std::string songTitle) {
        for (int i = 0; i < (int) m_songsDatabase.size(); i++) {
            if (m_songsDatabase[i].title() == songTitle) {
                return &m_songsDatabase[i];
            }
        }

        return nullptr;
    }

private:
    std::vector<Song> m_songsDatabase;
};

