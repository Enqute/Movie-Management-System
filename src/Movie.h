#pragma once

class Movie
{
private:
    struct Date
    {
        int Date;
        int Month;
        int Year;
    };

    enum class MovieType
    {
        ACTION = 1, ADVENTURE, COMMEDY, DRAMA,
        FANTANSY, HORROR, MYSTERY, ROMANCE,
        SCIFI, SPORTS, THRILLER, WESTERN
    };

    enum class Language
    {
        AMHARIC = 1, ARABIC, CHINESE, KOREAN, ENGLISH, FRENCH, HINDU, SPANISH
    };

    struct Node
    {
        MovieEntity Movie;
        Node* Next;
        Node* Prev;
    };

private:
    Node* m_Head = NULL;
    Node* m_Tail = NULL;

public:
    struct MovieEntity
    {
        int ID;
        std::string Title;
        float Rate;
        float Price;
        float Length;

        MovieType Genre;
        Date ReleasedDate;
        Language Lang;
    };

public:
    void AddFirst(const std::string& filepath);
    void AddLast(MovieEntity movie);

    void InsertAtIndex(int index, MovieEntity movie);
    void InsertById(MovieEntity movie, bool before, int ID);
    void InsertByTitle(MovieEntity movie, bool before, std::string title);

    void RemoveFirst();
    void RemoveLast();
    void RemoveById(int ID);
    void RemoveByTitle(std::string title);
    void RemoveByIndex(int index);
    void Remove(MovieEntity movie);
    void RemoveByLang(Language lang);
    void RemoveByGenre(MovieType genre);
    void RemoveByDate(Date releasedDate);

    MovieEntity GetById(int ID);
    MovieEntity GetByTitle(std::string title);
    MovieEntity GetByIndex(int index);
    MovieEntity* GetByLang(Language lang);
    MovieEntity* GetByGenre(MovieType genre, int top);
    MovieEntity* GetByDate(Date releasedDate, int top);
    MovieEntity* GetByPrice(float price, int top);
    MovieEntity* GetByRate(float rate, int top);
    MovieEntity* GetByLength(float length, int top);

    void UpdateById(int ID, Movie movie);
    void UpdateByTitle(std::string title, Movie movie);

    void DisplayMovieForward();
    void DisplayMovieBackward();

    inline bool IsMovieEmpty();

private:
    void printNode(Node* node);
    std::string toUpper(const char* string);

    Date stringToDate(std::string string);
    MovieType stringToGenre(const char* string);
    Language stringToLang(const char* string);

    std::string dateToString(Date date);
    std::string genreToString(MovieType genre);
    std::string langToString(Language lang);
};
