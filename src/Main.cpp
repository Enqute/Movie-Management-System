#include "Movie.h"

int main()
{
    AddFirst("movies.txt");
    DisplayForward();
    Movie movie;
    movie.ID = 104;
    movie.Title = "Henok Eshetu";
    movie.Rate = 10;
    movie.Price = 23.99;
    movie.Length = 3.2;
    movie.Genre = MovieType::ADVENTURE;
    movie.Lang = Language::AMHARIC;
    Date date;
    date.Month = 2;
    date.Date = 20;
    date.Year = 2022;
    movie.ReleasedDate = date;
    InsertById(movie, false, 103);
    movie.ID = 105;
    movie.Title = "Mahlet Eshetu";
    movie.Rate = 8.9;
    movie.Price = 25.99;
    movie.Length = 2.2;
    movie.Genre = MovieType::DRAMA;
    movie.Lang = Language::AMHARIC;
    date.Month = 1;
    date.Date = 10;
    date.Year = 2013;
    movie.ReleasedDate = date;
    InsertByTitle(movie, false, "Henok Eshetu");
    DisplayForward();
    RemoveByGenre("drama");
    DisplayForward();

    return 0;
}
