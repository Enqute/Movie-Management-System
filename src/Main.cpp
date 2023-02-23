#include <iostream>
#include <fstream>
#include <string>

// **********************************************************************************************************************
enum class MovieType;
enum class Language;

struct Date;
struct Movie;

Movie* g_Head = NULL;
Movie* g_Tail = NULL;

#define ASSERT(condition, message) if (!(condition)) { std::cout << message << std::endl; system("pause"); exit(-1); }

void AddMovieFirst(std::string filepath);
void AddMovieLast(Movie* movie);

void InsertMovieAtIndex(int index, Movie* movie);
void InsertMovieById(Movie* movie, bool before, int ID);
void InsertMovieByTitle(Movie* movie, bool before, std::string title);

void RemoveMovieFirst();
void RemoveMovieLast();
void RemoveMovieById(int ID);
void RemoveMovieByTitle(std::string title);
void RemoveMovieByIndex(int index);
void RemoveMovie(Movie movie);
void RemoveMovieByLang(Language lang);
void RemoveMovieByGenre(MovieType genre);
void RemoveMovieByDate(Date releasedDate);

Movie GetMovieById(int ID);
Movie GetMovieByTitle(std::string title);
Movie GetMovieByIndex(int index);
Movie* GetMoviesByLang(Language lang);
Movie* GetMoviesByGenre(MovieType genre, int top);
Movie* GetMoviesByDate(Date releasedDate, int top);
Movie* GetMoviesByPrice(float price, int top);
Movie* GetMoviesByRate(float rate, int top);
Movie* GetMoviesByLength(float length, int top);

void UpdateMovieById(int ID, Movie movie);
void UpdateMovieByTitle(std::string title, Movie movie);

void DisplayMovieForward();
void DisplayMovieBackward();

// **********************************************************************************************************************

MovieType stringToGenre(const char* string);
Date      stringToDate(std::string string);
Language  stringToLanguage(const char* string);
std::string toUpper(const char* string);
inline bool IsMovieEmpty();

// **********************************************************************************************************************

int main()
{
    AddMovieFirst("movies.txt");
    DisplayMovieForward();
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
    AMHARIC = 1, ARABIC, CHINESE, KOREAN, ENGLISH, FRENCH, HINDU, SPANISH
};

struct Movie
{
    int ID;
    std::string Title;
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

void AddMovieFirst(std::string filepath)
{
    std::fstream file;
    file.open(filepath, std::ios::out);
    
    ASSERT(file.is_open(), "[Error]: FileNotFoundException thrown from 'AddMovieFirst(...)'. There is a mistake at the filepath");
    
    int i = 0, count = 0;
    std::string fileContent[8];
    for (int i = 0; std::getline(file, fileContent[i]); i++)
    {
        if (i == 7)
        {
            if (fileContent[i] == "")
            {
                i--;
                continue;
            }

            Movie* movie = new Movie();
            movie->ID = std::stoi(fileContent[0]);
            movie->Title = fileContent[1];
            movie->Rate = std::stof(fileContent[2]);
            movie->Price = std::stof(fileContent[3]);
            movie->Length = std::stof(fileContent[4]);
            movie->Genre = stringToGenre(fileContent[5].c_str());
            movie->ReleasedDate = stringToDate(fileContent[6].c_str());
            movie->Lang = stringToLanguage(fileContent[7].c_str());
            movie->Prev = NULL;

            if (IsMovieEmpty())
                g_Head = g_Tail = movie;
            else
            {
                movie->Next = g_Head;
                g_Head->Prev = movie;
                g_Head = movie;
            }

            i = 0;
            count++;
        }
    }

    std::cout << "[Info]" << count << " movies are successfully added.";
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

void InsertMovieByTitle(Movie* movie, bool before, std::string Title)
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

void RemoveMovieByTitle(std::string title)
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
    return {};
}

Movie GetMovieByTitle(std::string title)
{
    // TODO: not implemented
    return {};
}

Movie GetMovieByIndex(int index)
{
    // TODO: not implemented
    return {};
}

Movie* GetMoviesByLang(Language lang, int top = -1)
{
    // TODO: not implemented
    return NULL;
}

Movie* GetMoviesByGenre(MovieType genre, int top = -1)
{
    // TODO: not implemented
    return NULL;
}

Movie* GetMoviesByDate(Date releasedDate, int top = -1)
{
    // TODO: not implemented
    return NULL;
}

Movie* GetMoviesByPrice(float price, int top)
{
    // TODO: not implemented
    return NULL;
}

Movie* GetMoviesByRate(float rate, int top)
{
    // TODO: not implemented
    return NULL;
}

Movie* GetMoviesByLength(float length, int top)
{
    // TODO: not implemented
    return NULL;
}

void UpdateMovieById(int ID, Movie movie)
{
    // TODO: not implemented
}

void UpdateMovieByTitle(std::string title, Movie movie)
{
    // TODO: not implemented
}

void DisplayMovieForward()
{
    if (IsMovieEmpty())
        std::cout << "[Error]: There is no movie to show you.";
    else
    {
        std::cout << "YOU ARE DISPLAYING ALL THE MOVIES FORWARD";
        for (Movie* movie = g_Head; movie != NULL; movie = movie->Next)
        {
            std::cout << "------------------------------------------------------------------------------\n";
            std::cout << "Title: " << movie->Title << std::endl;
            std::cout << "Rate: " << movie->Title << std::endl;
            std::cout << "Price: " << movie->Title << std::endl;
            std::cout << "Length: " << movie->Title << std::endl;
            std::cout << "Genre: " << movie->Title << std::endl;
            std::cout << "Released Date: " << movie->Title << std::endl;
            std::cout << "Language: " << movie->Title << std::endl;
            std::cout << "------------------------------------------------------------------------------";
        }
    }
}

void DisplayMovieBackward()
{
    if (IsMovieEmpty())
        std::cout << "[Error]: There is no movie to show you.";
    else
    {
        std::cout << "YOU ARE DISPLAYING ALL THE MOVIES BACKWARD";
        for (Movie* movie = g_Head; movie != NULL; movie = movie->Next)
        {
            std::cout << "------------------------------------------------------------------------------\n";
            std::cout << "Title: " << movie->Title << std::endl;
            std::cout << "Rate: " << movie->Title << std::endl;
            std::cout << "Price: " << movie->Title << std::endl;
            std::cout << "Length: " << movie->Title << std::endl;
            std::cout << "Genre: " << movie->Title << std::endl;
            std::cout << "Released Date: " << movie->Title << std::endl;
            std::cout << "Language: " << movie->Title << std::endl;
            std::cout << "------------------------------------------------------------------------------";
        }
    }
}

Date stringToDate(std::string string)
{
    Date date;
    date.Month = std::stoi(string.substr(0, 2));
    date.Date = std::stoi(string.substr(3, 5));
    date.Year = std::stoi(string.substr(6, 10));
    return date;
}

Language stringToLanguage(const char* string)
{
    if (toUpper(string) == "AMHARIC") return Language::AMHARIC;
    else if (toUpper(string) == "ARABIC") return Language::ARABIC;
    else if (toUpper(string) == "CHINESE") return Language::CHINESE;
    else if (toUpper(string) == "ENGLISH") return Language::ENGLISH;
    else if (toUpper(string) == "FRENCH") return Language::FRENCH;
    else if (toUpper(string) == "HINDU") return Language::HINDU;
    else if (toUpper(string) == "KOREAN") return Language::KOREAN;
    else if (toUpper(string) == "SPANISH") return Language::SPANISH;
    else return Language::ENGLISH;
}

MovieType stringToGenre(const char* string)
{
    if (toUpper(string) == "ACTION") return MovieType::ACTION;
    else if (toUpper(string) == "ADVENTURE") return MovieType::ADVENTURE;
    else if (toUpper(string) == "COMMEDY") return MovieType::COMMEDY;
    else if (toUpper(string) == "DRAMA") return MovieType::DRAMA;
    else if (toUpper(string) == "FANTANSY") return MovieType::FANTANSY;
    else if (toUpper(string) == "HORROR") return MovieType::HORROR;
    else if (toUpper(string) == "MYSTERY") return MovieType::MYSTERY;
    else if (toUpper(string) == "ROMANCE") return MovieType::ROMANCE;
    else if (toUpper(string) == "SCIFI") return MovieType::SCIFI;
    else if (toUpper(string) == "SPORTS") return MovieType::SPORTS;
    else if (toUpper(string) == "THRILLER") return MovieType::THRILLER;
    else if (toUpper(string) == "WESTERN") return MovieType::WESTERN;
    else return MovieType::ACTION;
}

std::string toUpper(const char* string)
{
    char* str = (char*)malloc(sizeof(string));
    for (int i = 0; i < (sizeof(string)); i++)
    {
        char temp = string[i];
        if (((int)temp) >= 97 && ((int)temp) <= 122)
            str[i] = temp - 32;
    }
    return str;
}

bool IsMovieEmpty()
{
    return (g_Head == NULL);
}
