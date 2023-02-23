#include <iostream>

// **********************************************************************************************************************
enum class MovieType;
enum class Language;

struct Date;
struct Movie;

Movie* g_Head = NULL;
Movie* g_Tail = NULL;

void AddMovieFirst(char filepath[]);
void AddMovieLast(Movie* movie);

void InsertMovieAtIndex(int index, Movie* movie);
void InsertMovieById(Movie* movie, bool before, int ID);
void InsertMovieByTitle(Movie* movie, bool before, char title[]);

void RemoveMovieFirst();
void RemoveMovieLast();
void RemoveMovieById(int ID);
void RemoveMovieByTitle(char title[]);
void RemoveMovieByIndex(int index);
void RemoveMovie(Movie movie);
void RemoveMovieByLang(Language lang);
void RemoveMovieByGenre(MovieType genre);
void RemoveMovieByDate(Date releasedDate);

Movie GetMovieById(int ID);
Movie GetMovieByTitle(char title[]);
Movie GetMovieByIndex(int index);
Movie* GetMoviesByLang(Language lang);
Movie* GetMoviesByGenre(MovieType genre);
Movie* GetMoviesByDate(Date releasedDate);

void UpdateMovieById(int ID, Movie movie);
void UpdateMovieByTitle(char title[], Movie movie);
// **********************************************************************************************************************

int main()
{

}

// **********************************************************************************************************************
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
    AMHARIC = 1, ARABIC, ENGLISH, FRENCH, HINDU, SPANISH
};

struct Movie
{
    int ID;
    char Title[100];
    float Rate;
    float Price;
    float Length;

    MovieType Genre;
    Date ReleasedDate;
    Language Lang;

    Movie* Next;
    Movie* Prev;
};
// **********************************************************************************************************************

void AddMovieFirst(char filepath[])
{
    // TODO: not implemented
}

void AddMovieLast(Movie* movie)
{
    // TODO: not implemented
}

void InsertMovieAtIndex(int index, Movie* movie)
{
	// TODO: not implemented
}

void InsertMovieById(Movie* movie, bool before, int ID)
{
    // TODO: not implemented
}

void InsertMovieByTitle(Movie* movie, bool before, char Title[])
{
    // TODO: not implemented
}

void RemoveMovieFirst()
{
    // TODO: not implemented
}

void RemoveMovieLast()
{
    // TODO: not implemented
}

void RemoveMovieByIndex(int index)
{
	// TODO: not implemented
}

void RemoveMovieById(int ID)
{
    // TODO: not implemented
}

void RemoveMovieByTitle(char title[])
{
	// TODO: not implemented
}

void RemoveMovieByGenre(MovieType genre)
{
    // TODO: not implemented
}

void RemoveMovieByLang(Language lang)
{
    // TODO: not implemented
}

void RemoveMovieByDate(Date releasedDate)
{
    // TODO: not implemented
}

void RemoveMovie(Movie movie)
{
    // TODO: not implemented
}

Movie GetMovieById(int ID)
{
    // TODO: not implemented
}

Movie GetMovieByTitle(char title[])
{
    // TODO: not implemented
}

Movie GetMovieByIndex(int index)
{
    // TODO: not implemented
}

Movie* GetMoviesByLang(Language lang)
{
    // TODO: not implemented
}

Movie* GetMoviesByGenre(MovieType genre)
{
    // TODO: not implemented
}

Movie* GetMoviesByDate(Date releasedDate)
{
    // TODO: not implemented
}

void UpdateMovieById(int ID, Movie movie)
{
    // TODO: not implemented
}

void UpdateMovieByTitle(char title[], Movie movie)
{
    // TODO: not implemented
}
