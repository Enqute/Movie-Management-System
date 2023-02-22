#include <iostream>

// **********************************************************************************************************************
enum Type;
enum Language;

struct Date;
struct Movie;

Movie* Head = NULL;
Movie* Tail = NULL;

void AddMovieFirst(char filepath[]);
void AddMovieLast(Movie* movie);
void InsertMovieById(Movie* movie, bool before, int ID);
void InsertMovieByTitle(Movie* movie, bool before, char Title[]);

void RemoveMovieFirst();
void RemoveMovieLast();
void RemoveMovieById(int ID);
void InsertMovieByTitle(char Title[]);
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

enum Type
{
    ACTION = 1, ADVENTURE, COMMEDY, DRAMA, 
    FANTANSY, HORROR, MYSTERY, ROMANCE, 
    SCIFI, SPORTS, THRILLER, WESTERN
};

enum Language
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

    Type MovieType;
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

void RemoveMovieById(int ID)
{
    // TODO: not implemented
}

void InsertMovieByTitle(char Title[])
{
    // TODO: not implemented
}
