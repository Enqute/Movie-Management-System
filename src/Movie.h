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
    Movie() = delete;
    Movie(const std::string& filepath)
        : m_FilePath(filepath)
    { 
    }

public:
    void AddMovieFirst();
    void AddMovieLast(MovieEntity* movie);

    void InsertMovieAtIndex(int index, MovieEntity* movie);
    void InsertMovieById(MovieEntity* movie, bool before, int ID);
    void InsertMovieByTitle(MovieEntity* movie, bool before, std::string title);

    void RemoveMovieFirst();
    void RemoveMovieLast();
    void RemoveMovieById(int ID);
    void RemoveMovieByTitle(std::string title);
    void RemoveMovieByIndex(int index);
    void RemoveMovie(MovieEntity movie);
    void RemoveMovieByLang(Language lang);
    void RemoveMovieByGenre(MovieType genre);
    void RemoveMovieByDate(Date releasedDate);

    MovieEntity GetMovieById(int ID);
    MovieEntity GetMovieByTitle(std::string title);
    MovieEntity GetMovieByIndex(int index);
    MovieEntity* GetMoviesByLang(Language lang);
    MovieEntity* GetMoviesByGenre(MovieType genre, int top);
    MovieEntity* GetMoviesByDate(Date releasedDate, int top);
    MovieEntity* GetMoviesByPrice(float price, int top);
    MovieEntity* GetMoviesByRate(float rate, int top);
    MovieEntity* GetMoviesByLength(float length, int top);

    void UpdateMovieById(int ID, Movie movie);
    void UpdateMovieByTitle(std::string title, Movie movie);

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

private:
    std::string m_FilePath;
    Node* m_Head = NULL;
    Node* m_Tail = NULL;
};
