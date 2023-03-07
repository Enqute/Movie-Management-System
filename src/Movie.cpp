#include "Movie.h"

Node* m_Head = NULL;
Node* m_Tail = NULL;
int m_Size = 0;

void AddFirst(const std::string& filepath)
{
    std::ifstream file(filepath);

    ASSERT(file.is_open(), "[Error]: FileNotFoundException thrown from 'AddMovieFirst(...)'. There is a mistake at the filepath");

    int i = 0, count = 0;
    std::string fileContent[8];
    for (int i = 0; !file.eof(); i++)
    {
        std::string content;
        if (!(i < 0))
            std::getline(file, content);
        if (content.find("=") != std::string::npos)
        {
            i = -1;
            continue;
        }
        else fileContent[i] = content;
        if (i == 7)
        {
            Movie movie;
            movie.ID = std::atoi(fileContent[0].c_str());
            movie.Title = fileContent[1];
            movie.Rate = std::atof(fileContent[2].c_str());
            movie.Price = std::atof(fileContent[3].c_str());
            movie.Length = std::atof(fileContent[4].c_str());
            movie.Genre = stringToGenre(fileContent[5].c_str());
            movie.ReleasedDate = stringToDate(fileContent[6].c_str());
            movie.Lang = stringToLang(fileContent[7].c_str());

            AddFirst(movie);

            i = -1;
            count++;
        }
    }

    file.close();
    std::cout << "[Success] " << count << " movies are successfully added from \"" << filepath << "\".\n\n";
}

void AddFirst(Movie movie)
{
    Node* node = new Node();
    node->Movie = movie;
    node->Next = NULL;
    node->Prev = NULL;

    if (IsEmpty())
        m_Head = m_Tail = node;
    else
    {
        node->Next = m_Head;
        m_Head->Prev = node;
        m_Head = node;
    }
    m_Size++;

    std::cout << "[Success] \"" << node->Movie.Title.c_str() << "\" is successfully added.\n";
}

void AddLast(Movie movie)
{
    Node* node = new Node();
    node->Movie = movie;
    node->Next = NULL;
    node->Prev = NULL;

    if (IsEmpty())
        m_Head = m_Tail = node;
    else
    {
        node->Prev = m_Tail;
        m_Tail->Next = node;
        m_Tail = node;
    }
    m_Size++;

    std::cout << "[Success] \"" << node->Movie.Title.c_str() << "\" is successfully added.\n";
}

void InsertAtIndex(int index, Movie movie)
{
    Node* node = new Node();
    node->Movie = movie;
    node->Next = NULL;
    node->Prev = NULL;

    int counter = 0;
    Node* trav = m_Head;
    for (; trav != NULL && counter != index - 1; trav = trav->Next, counter++);
    node->Next = trav->Next;
    trav->Next->Prev = node;
    trav->Next = node;
    node->Prev = trav;

    m_Size++;

    std::cout << "[Success] \"" << node->Movie.Title.c_str()
        << "\" is successfully inserted at index " << index << "\n";
}

void InsertById(Movie movie, bool before, int ID)
{
    Node* node = new Node();
    node->Movie = movie;
    node->Next = NULL;
    node->Prev = NULL;

    Node* trav = m_Head;
    for (; trav != NULL && trav->Movie.ID != ID; trav = trav->Next);
    if (before)
    {
        if (m_Head->Movie.ID == ID)
            AddFirst(node->Movie);
        else
        {
            Node* temp = trav->Prev;
            trav->Prev = node;
            node->Next = trav;
            temp->Next = node;
            node->Prev = temp;
            std::cout << "[Success] \"" << node->Movie.Title.c_str()
                << "\" is successfully inserted " << "before MovieID " << trav->Movie.ID << "\n";
        }
    }
    else
    {
        if (m_Tail->Movie.ID == ID)
            AddLast(node->Movie);
        else
        {
            Node* temp = trav->Next;
            trav->Next = node;
            node->Prev = trav;
            temp->Prev = node;
            node->Next = temp;
            std::cout << "[Success] \"" << node->Movie.Title.c_str()
                << "\" is successfully inserted " << "after MovieID " << trav->Movie.ID << "\n";
        }
    }

    m_Size++;
}

void InsertByTitle(Movie movie, bool before, std::string title)
{
    Node* node = new Node();
    node->Movie = movie;
    node->Next = NULL;
    node->Prev = NULL;

    Node* trav = m_Head;
    for (; trav != NULL && trav->Movie.Title != title; trav = trav->Next);
    if (before)
    {
        if (m_Head->Movie.Title == title)
            AddFirst(node->Movie);
        else
        {
            Node* temp = trav->Prev;
            trav->Prev = node;
            node->Next = trav;
            temp->Next = node;
            node->Prev = temp;
            std::cout << "[Success] \"" << node->Movie.Title.c_str()
                << "\" is successfully inserted " << "before movie \""
                << trav->Movie.Title.c_str() << "\"\n";
        }
    }
    else
    {
        if (m_Tail->Movie.Title == title)
            AddLast(node->Movie);
        else
        {
            Node* temp = trav->Next;
            trav->Next = node;
            node->Prev = trav;
            temp->Prev = node;
            node->Next = temp;
            std::cout << "[Success] \"" << node->Movie.Title.c_str()
                << "\" is successfully inserted " << "after movie \""
                << trav->Movie.Title.c_str() << "\"\n";
        }
    }

    m_Size++;
}

void RemoveFirst()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveFirst()'. The list is empty.");
    Node* node = m_Head;
    std::string movie = node->Movie.Title;
    m_Head = m_Head->Next;
    m_Head->Prev = NULL;
    delete node;
    m_Size--;
}

void RemoveLast()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveLast()'. The list is empty.");
    Node* node = m_Tail;
    std::string movie = node->Movie.Title;
    m_Tail = m_Tail->Prev;
    m_Tail->Next = NULL;
    delete node;
    m_Size--;
}

void RemoveById(int ID)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveById(...)'. The list is empty.");
    ASSERT(Contains(ID), "[Error] IllegalAccessException thrown from 'RemoveById(...)'. The movieID is not in the list.");

    Node* node = m_Head;
    for (; node->Movie.ID != ID; node = node->Next);
    std::cout << node->Movie.Title << "-----------------------\n";
    Remove(node->Movie);
}

void RemoveByTitle(std::string title)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByTitle(...)'. The list is empty.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.Title != title; node = node->Next);
    Remove(node->Movie);
}

void RemoveByIndex(int index)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByIndex(...)'. The list is empty.");
    ASSERT(index >= 0 && index < m_Size, "[Error] IndexOutOfBound thrown from 'RemoveByIndex(...)'. The index is not available.");

    Node* node = m_Head;
    for (int i = 0; i < index; node = node->Next, i++);
    Remove(node->Movie);
}

void Remove(Movie movie)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'Remove(...)'. The list is empty.");
    ASSERT(Contains(movie.ID), "[Error] IllegalAccessException thrown from 'Remove(...)'. The movie is not in the list.");

    int index = IndexOf(movie);
    if (index == 0)
        RemoveFirst();
    else if (index == m_Size - 1)
        RemoveLast();
    else
    {
        Node* node = m_Head;
        for (int i = 0; node != NULL && i <= index; node = node->Next, i++);
        Node* temp = node;
        node->Prev->Next = node->Next;
        node->Next->Prev = node->Prev;
        delete temp;
    }
    m_Size--;
    std::cout << "[Success] \"" << movie.Title << "\" is successfully deleted.\n";
}

void RemoveByLang(std::string language)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByLang(...)'. The list is empty.");

    Language lang = stringToLang(language.c_str());
    int countDeleted = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (node->Movie.Lang == lang)
        {
            if (node->Movie.ID == m_Head->Movie.ID)
                RemoveFirst();
            else if (node->Movie.ID == m_Tail->Movie.ID)
                RemoveLast();
            else
            {
                Node* temp = node;
                node->Prev->Next = node->Next;
                node->Next->Prev = node->Prev;
                delete temp;
            }
            countDeleted++;
        }
    }
    std::string _lang = langToString(lang);
    if (countDeleted == 0)
        std::cout << "[Warning] There is no movie with \"" << _lang << "\" language.\n";
    else std::cout << "[Success] " << countDeleted << " movies deleted with \"" << _lang << "\" language.\n";
}

void RemoveByGenre(std::string movieType)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByGenre(...)'. The list is empty.");

    MovieType genre = stringToGenre(movieType.c_str());
    int countDeleted = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (node->Movie.Genre == genre)
        {
            if (node->Movie.Genre == m_Head->Movie.Genre)
                RemoveFirst();
            else if (node->Movie.Genre == m_Tail->Movie.Genre)
                RemoveLast();
            else
            {
                Node* temp = node;
                node->Prev->Next = node->Next;
                node->Next->Prev = node->Prev;
                delete temp;
            }
            countDeleted++;
        }
    }
    std::string _genre = genreToString(genre);
    if (countDeleted == 0)
        std::cout << "[Warning] There is no  \"" << _genre << "\" movie.\n";
    else std::cout << "[Success] " << countDeleted << " \"" << _genre << "\" movies deleted.\n";
}

void RemoveByDate(std::string date)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByDate(...)'. The list is empty.");
// TODO: NOT IMLEMENTED
    int countDeleted = 0;
    Date _date = stringToDate(date);
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (node->Movie.ReleasedDate == _date)
        {
            if (node->Movie.ReleasedDate.Date == m_Head->Movie.ReleasedDate.Date)
                RemoveFirst();
            else if (node->Movie.ReleasedDate.Date == m_Tail->Movie.ReleasedDate.Date)
                RemoveLast();
            else
            {
                Node* temp = node;
                node->Prev->Next = node->Next;
                node->Next->Prev = node->Prev;
                delete temp;
            }
            countDeleted++;
        }
    }
    
    if (countDeleted == 0)
        std::cout << "[Warning] There is no mpvies with the date " << _date << ".\n";
    else std::cout << "[Success] " << countDeleted << " movies deleted by the date " << _date << ".\n";
}

Movie GetById(int ID)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByDate(...)'. The list is empty.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.ID != ID; node = node->Next);

    return node->Movie;
}

Movie GetByTitle(std::string title)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByTitle(...)'. The list is empty.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.Title != title; node = node->Next);

    return node->Movie;
}

Movie GetByIndex(int index)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByDate(...)'. The list is empty.");

    int counter = 0;
    Node* node = m_Head;
    for (; node != NULL && index != counter; node = node->Next, counter++);

    return node->Movie;
}

Movie GetByMinPrice()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByMinPrice(...)'. The list is empty.");

    float minPrice = m_Head->Movie.Price;
    int minPriceIndex = 0;
    int counter = 0;
    for (Node* node = m_Head->Next; node != NULL; node = node->Next, counter++)
    {
        if (minPrice > node->Movie.Price)
        {
            minPrice = node->Movie.Price;
            minPriceIndex = counter;
        }
    }
    return GetByIndex(minPriceIndex);
}

Movie GetByMinRating()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByMinRating(...)'. The list is empty.");

    float minRate = m_Head->Movie.Rate;
    int minRateIndex = 0;
    int counter = 0;
    for (Node* node = m_Head->Next; node != NULL; node = node->Next, counter++)
    {
        if (minRate > node->Movie.Rate)
        {
            minRate = node->Movie.Rate;
            minRateIndex = counter;
        }
    }
    return GetByIndex(minRateIndex);
}

Movie GetByMaxPrice()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByMaxPrice(...)'. The list is empty.");

    float maxPrice = m_Head->Movie.Price;
    int maxPriceIndex = 0;
    int counter = 0;
    for (Node* node = m_Head->Next; node != NULL; node = node->Next, counter++)
    {
        if (maxPrice < node->Movie.Price)
        {
            maxPrice = node->Movie.Price;
            maxPriceIndex = counter;
        }
    }
    return GetByIndex(maxPriceIndex);
}

Movie GetByMaxRating()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByMaxRating(...)'. The list is empty.");

    float maxRate = m_Head->Movie.Rate;
    int maxRateIndex = 0;
    int counter = 0;
    for (Node* node = m_Head->Next; node != NULL; node = node->Next, counter++)
    {
        if (maxRate < node->Movie.Rate)
        {
            maxRate = node->Movie.Rate;
            maxRateIndex = counter;
        }
    }
    return GetByIndex(maxRateIndex);
}

Movie GetByAvePrice()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByAvePrice(...)'. The list is empty.");
    
    float totalPrice = 0.f;
    for (Node* node = m_Head; node != NULL; node = node->Next)
        totalPrice += node->Movie.Price;
    float averagePrice = totalPrice / m_Size;
    return averagePrice;
}

Movie GetByAveLength()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByAveLength(...)'. The list is empty.");
    
    float totalLength = 0.f;
    for (Node* node = m_Head; node != NULL; node = node->Next)
        totalLength += node->Movie.Length;
    float averageLength = totalLength / m_Size;
    return averageLength;
}

Movie* GetByLang(std::string lang)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByLang(...)'. The list is empty.");

    Language _lang = stringToLang(lang);
    int counter = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (_lang == node->Movie.Lang)
            counter++;
    }

    int index = 0;
    Movie* movies = (Movie*)malloc(sizeof(Movie) * counter);
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (_lang == node->Movie.Lang)
        {
            movies[index] = node->Movie;
            index++;
        }
    }

    return movies;
}

Movie* GetByGenre(std::string genre, int top)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByGenre(...)'. The list is empty.");

    Genre _genre = stringToGenre(genre);
    int counter = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (_genre == node->Movie.Genre)
            counter++;
    }

    int index = 0;
    Movie* movies = (Movie*)malloc(sizeof(Movie) * counter);
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (_genre == node->Movie.Genre)
        {
            movies[index] = node->Movie;
            index++;
        }
    }

    return movies;
}

Movie* GetByDate(std::string releasedDate, int top)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByLang(...)'. The list is empty.");
// TODO: NOT IMPLEMENTED
    Language _lang = stringToLang(lang);
    int counter = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (_lang == node->Movie.Lang)
            counter++;
    }

    int index = 0;
    Movie* movies = (Movie*)malloc(sizeof(Movie) * counter);
    for (Node* node = m_Head; node != NULL; node = node->Next, index++)
    {
        if (_lang == node->Movie.Lang)
            movies[index] = node->Movie;
    }

    return movies;
}

Movie* GetByPrice(float price, int top)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByPrice(...)'. The list is empty.");

    int counter = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (price == node->Movie.Price)
            counter++;
    }

    int index = 0;
    Movie* movies = (Movie*)malloc(sizeof(Movie) * counter);
    for (Node* node = m_Head; node != NULL; node = node->Next, index++)
    {
        if (price == node->Movie.Price)
            movies[index] = node->Movie;
    }

    return movies;
}

Movie* GetByRate(float rate, int top)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByRate(...)'. The list is empty.");

    int counter = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (rate == node->Movie.Rate)
            counter++;
    }

    int index = 0;
    Movie* movies = (Movie*)malloc(sizeof(Movie) * counter);
    for (Node* node = m_Head; node != NULL; node = node->Next, index++)
    {
        if (rate == node->Movie.Rate)
            movies[index] = node->Movie;
    }

    return movies;
}

Movie* GetByLength(float length, int top)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByLength(...)'. The list is empty.");

    int counter = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (length == node->Movie.Length)
            counter++;
    }

    int index = 0;
    Movie* movies = (Movie*)malloc(sizeof(Movie) * counter);
    for (Node* node = m_Head; node != NULL; node = node->Next, index++)
    {
        if (length == node->Movie.Length)
            movies[index] = node->Movie;
    }

    return movies;
}

void UpdateById(int ID, Movie movie)
{

}

void UpdateByTitle(std::string title, Movie movie)
{

}

void DisplayForward()
{
    if (IsEmpty())
        std::cout << "[Error]: There is no movie to show you.\n";
    else
    {
        std::cout << "YOU ARE DISPLAYING ALL THE MOVIES FORWARD\n";
        for (Node* node = m_Head; node != NULL; node = node->Next)
            printNode(*node);
    }
}

void DisplayBackward()
{
    if (IsEmpty())
        std::cout << "[Error]: There is no movie to show you.\n";
    else
    {
        std::cout << "YOU ARE DISPLAYING ALL THE MOVIES BACKWARD\n";
        for (Node* node = m_Tail; node != NULL; node = node->Prev)
            printNode(*node);
    }
}

inline bool IsEmpty()
{
    return (m_Head == NULL);
}

int IndexOf(int movieID)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'IndexOf(...)'. The list is empty.");
    int i = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next, i++)
        if (node->Movie.ID == movieID)
            return i;
    return -1;
}

int IndexOf(Movie movie)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'IndexOf(...)'. The list is empty.");
    int i = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next, i++)
        if (node->Movie.ID == movie.ID)
            return i;
    return -1;
}

bool Contains(int movieID)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'Contains(...)'. The list is empty.");
    return (IndexOf(movieID) != -1);
}

void printNode(Node node)
{
    std::cout << "------------------------------------------------------------------------------\n";
    std::cout << "ID: " << node.Movie.ID << "\n";
    std::cout << "Title: " << node.Movie.Title.c_str() << "\n";
    std::cout << "Rate: " << node.Movie.Rate << " / 10\n";
    std::cout << "Price: $" << node.Movie.Price << "\n";
    std::cout << "Length: " << node.Movie.Length << " Hr\n";
    std::cout << "Genre: " << genreToString(node.Movie.Genre).c_str() << "\n";
    std::cout << "Released Date: " << dateToString(node.Movie.ReleasedDate).c_str() << "\n";
    std::cout << "Language: " << langToString(node.Movie.Lang).c_str() << "\n";
    std::cout << "------------------------------------------------------------------------------\n";
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

Date stringToDate(std::string string)
{
    Date date;
    std::string _date, _month, _year;
    for (int i = 0; i < 2; i++)
        _month += string[i];
    for (int i = 3; i < 5; i++)
        _date += string[i];
    for (int i = 6; i < 10; i++)
        _year += string[i];

    date.Month = std::atoi(_month.c_str());
    date.Date = std::atoi(_date.c_str());
    date.Year = std::atoi(_year.c_str());

    return date;
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

Language stringToLang(const char* string)
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

std::string dateToString(Date date)
{
    std::string _date = "";
    _date += std::to_string(date.Month) + "/";
    _date += std::to_string(date.Date) + "/";
    _date += std::to_string(date.Year);
    return _date;
}

std::string genreToString(MovieType genre)
{
    if (genre == MovieType::ACTION) return "ACTION";
    else if (genre == MovieType::ADVENTURE) return "ADVENTURE";
    else if (genre == MovieType::COMMEDY) return "COMMEDY";
    else if (genre == MovieType::DRAMA) return "DRAMA";
    else if (genre == MovieType::FANTANSY) return "FANTANSY";
    else if (genre == MovieType::HORROR) return "HORROR";
    else if (genre == MovieType::MYSTERY) return "MYSTERY";
    else if (genre == MovieType::ROMANCE) return "ROMANCE";
    else if (genre == MovieType::SCIFI) return "SCIFI";
    else if (genre == MovieType::SPORTS) return "SPORTS";
    else if (genre == MovieType::THRILLER) return "THRILLER";
    else if (genre == MovieType::WESTERN) return "WESTERN";
    else return "ACTION";
}

std::string langToString(Language lang)
{
    if (lang == Language::AMHARIC) return "AMHARIC";
    else if (lang == Language::ARABIC) return "ARABIC";
    else if (lang == Language::CHINESE) return "CHINESE";
    else if (lang == Language::ENGLISH) return "ENGLISH";
    else if (lang == Language::FRENCH) return "FRENCH";
    else if (lang == Language::HINDU) return "HINDU";
    else if (lang == Language::KOREAN) return "KOREAN";
    else if (lang == Language::SPANISH) return "SPANISH";
    else return "ENGLISH";
}
