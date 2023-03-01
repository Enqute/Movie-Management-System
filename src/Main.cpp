#include "Core.h"

int main()
{
    Movie movie;
    movie.AddFirst("movies.txt");
    movie.DisplayForward();

    return 0;
}
