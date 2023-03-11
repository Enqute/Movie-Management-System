#include "Movie.h"

#include "Core.h"
#include <fstream>
#include <cstdlib>
#include <algorithm>

Node* m_Head = NULL;
Node* m_Tail = NULL;
int m_Size = 0;

void AddFirst(const char* filepath)
{
    std::ifstream file(filepath);

    ASSERT(file.is_open(), "[Error]: FileNotFoundException thrown from 'AddMovieFirst(...)'. There is a mistake at the filepath");

    int count = 0;
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

    int countDeleted = 0;
    Date _date = stringToDate(date);
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (dateToString(node->Movie.ReleasedDate) == dateToString(_date))
        {
            Date nd = node->Movie.ReleasedDate;
            Date hd = m_Head->Movie.ReleasedDate;
            Date td = m_Tail->Movie.ReleasedDate;
            if (nd.Date == hd.Date && nd.Month == hd.Month && nd.Year == hd.Year)
                RemoveFirst();
            else if (nd.Date == td.Date && nd.Month == td.Month && nd.Year == td.Year)
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
        std::cout << "[Warning] There is no mpvies with the date " << date << ".\n";
    else std::cout << "[Success] " << countDeleted << " movies deleted by the date " << date << ".\n";
}

void RemoveByMinPrice()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByMinPrice()'. The list is empty.");
    ASSERT(m_Size > 1, "[Error] There is no additional movie to compare with.");

    float minPrice = m_Head->Movie.Price;
    int minPriceIndex = 0;
    int counter = 0;
    Node* node = m_Head->Next;
    for (; node != NULL; node = node->Next, counter++)
    {
        if (minPrice > node->Movie.Price)
        {
            minPrice = node->Movie.Price;
            minPriceIndex = counter;
        }
    }

    if (minPriceIndex == 0)
        RemoveFirst();
    else if (minPriceIndex == m_Size - 1)
        RemoveLast();
    else
    {
        Node* node2 = m_Head;
        int index = 0;
        for (; index <= minPriceIndex; node2 = node2->Next, index++);
        Node* temp = node2;
        node2->Prev->Next = node2->Next;
        node2->Next->Prev = node2->Prev;
        delete temp;
    }
}

void RemoveByMinRate()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByMinRate()'. The list is empty.");
    ASSERT(m_Size > 1, "[Error] There is no additional movie to compare with.");

    float minRate = m_Head->Movie.Rate;
    int minRateIndex = 0;
    int counter = 0;
    Node* node = m_Head->Next;
    for (; node != NULL; node = node->Next, counter++)
    {
        if (minRate > node->Movie.Rate)
        {
            minRate = node->Movie.Rate;
            minRateIndex = counter;
        }
    }

    if (minRateIndex == 0)
        RemoveFirst();
    else if (minRateIndex == m_Size - 1)
        RemoveLast();
    else
    {
        Node* node2 = m_Head;
        int index = 0;
        for (; index <= minRateIndex; node2 = node2->Next, index++);
        Node* temp = node2;
        node2->Prev->Next = node2->Next;
        node2->Next->Prev = node2->Prev;
        delete temp;
    }
}

void RemoveByMaxPrice()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByMaxPrice()'. The list is empty.");
    ASSERT(m_Size > 1, "[Error] There is no additional movie to compare with.");

    float maxPrice = m_Head->Movie.Price;
    int maxPriceIndex = 0;
    int counter = 0;
    Node* node = m_Head->Next;
    for (; node != NULL; node = node->Next, counter++)
    {
        if (maxPrice < node->Movie.Price)
        {
            maxPrice = node->Movie.Price;
            maxPriceIndex = counter;
        }
    }

    if (maxPriceIndex == 0)
        RemoveFirst();
    else if (maxPriceIndex == m_Size - 1)
        RemoveLast();
    else
    {
        Node* node2 = m_Head;
        int index = 0;
        for (; index <= maxPriceIndex; node2 = node2->Next, index++);
        Node* temp = node2;
        node2->Prev->Next = node2->Next;
        node2->Next->Prev = node2->Prev;
        delete temp;
    }
}

void RemoveByMaxRate()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'RemoveByMaxRate()'. The list is empty.");
    ASSERT(m_Size > 1, "[Error] There is no additional movie to compare with.");

    float maxRate = m_Head->Movie.Rate;
    int maxRateIndex = 0;
    int counter = 0;
    Node* node = m_Head->Next;
    for (; node != NULL; node = node->Next, counter++)
    {
        if (maxRate < node->Movie.Rate)
        {
            maxRate = node->Movie.Rate;
            maxRateIndex = counter;
        }
    }

    if (maxRateIndex == 0)
        RemoveFirst();
    else if (maxRateIndex == m_Size - 1)
        RemoveLast();
    else
    {
        Node* node2 = m_Head;
        int index = 0;
        for (; index <= maxRateIndex; node2 = node2->Next, index++);
        Node* temp = node2;
        node2->Prev->Next = node2->Next;
        node2->Next->Prev = node2->Prev;
        delete temp;
    }
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

float GetByAvePrice()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByAvePrice(...)'. The list is empty.");

    float totalPrice = 0.f;
    for (Node* node = m_Head; node != NULL; node = node->Next)
        totalPrice += node->Movie.Price;
    float averagePrice = totalPrice / m_Size;
    return averagePrice;
}

float GetByAveLength()
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

    Language _lang = stringToLang(lang.c_str());
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

    MovieType _genre = stringToGenre(genre.c_str());
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
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'GetByDate(...)'. The list is empty.");

    Date _date = stringToDate(releasedDate);
    Movie* movies = NULL;

    int index = 0, counter = 0;

    if (_date.Date != 0 && _date.Month != 0 && _date.Year != 0)
    {
        for (Node* node = m_Head; node != NULL; node = node->Next)
        {
            Date nd = node->Movie.ReleasedDate;
            if (_date.Date == nd.Date && _date.Month == nd.Month && _date.Year == nd.Year)
                counter++;
        }

        movies = (Movie*)malloc(sizeof(Movie) * counter);
        for (Node* node = m_Head; node != NULL; node = node->Next, index++)
        {
            Date nd = node->Movie.ReleasedDate;
            if (_date.Date == nd.Date && _date.Month == nd.Month && _date.Year == nd.Year)
                movies[index] = node->Movie;
        }
    }
    else if (_date.Date != 0 && _date.Month != 0 && _date.Year == 0)
    {
        for (Node* node = m_Head; node != NULL; node = node->Next)
        {
            Date nd = node->Movie.ReleasedDate;
            if (_date.Date == nd.Date && _date.Month == nd.Month)
                counter++;
        }

        movies = (Movie*)malloc(sizeof(Movie) * counter);
        for (Node* node = m_Head; node != NULL; node = node->Next, index++)
        {
            Date nd = node->Movie.ReleasedDate;
            if (_date.Date == nd.Date && _date.Month == nd.Month)
                movies[index] = node->Movie;
        }
    }
    else if (_date.Date != 0 && _date.Month == 0 && _date.Year != 0)
    {
        for (Node* node = m_Head; node != NULL; node = node->Next)
        {
            Date nd = node->Movie.ReleasedDate;
            if (_date.Date == nd.Date && _date.Year == nd.Year)
                counter++;
        }

        movies = (Movie*)malloc(sizeof(Movie) * counter);
        for (Node* node = m_Head; node != NULL; node = node->Next, index++)
        {
            Date nd = node->Movie.ReleasedDate;
            if (_date.Date == nd.Date && _date.Year == nd.Year)
                movies[index] = node->Movie;
        }
    }
    else if (_date.Date != 0 && _date.Month == 0 && _date.Year == 0)
    {
        for (Node* node = m_Head; node != NULL; node = node->Next)
        {
            if (_date.Date == node->Movie.ReleasedDate.Date)
                counter++;
        }

        movies = (Movie*)malloc(sizeof(Movie) * counter);
        for (Node* node = m_Head; node != NULL; node = node->Next, index++)
        {
            if (_date.Date == node->Movie.ReleasedDate.Date)
                movies[index] = node->Movie;
        }
    }

    else if (_date.Date == 0 && _date.Month != 0 && _date.Year != 0)
    {
        for (Node* node = m_Head; node != NULL; node = node->Next)
        {
            Date nd = node->Movie.ReleasedDate;
            if (_date.Month == nd.Month && _date.Year == nd.Year)
                counter++;
        }

        movies = (Movie*)malloc(sizeof(Movie) * counter);
        for (Node* node = m_Head; node != NULL; node = node->Next, index++)
        {
            Date nd = node->Movie.ReleasedDate;
            if (_date.Date == nd.Month && _date.Year == nd.Year)
                movies[index] = node->Movie;
        }
    }
    else if (_date.Date == 0 && _date.Month != 0 && _date.Year == 0)
    {
        for (Node* node = m_Head; node != NULL; node = node->Next)
        {
            if (_date.Month == node->Movie.ReleasedDate.Month)
                counter++;
        }

        movies = (Movie*)malloc(sizeof(Movie) * counter);
        for (Node* node = m_Head; node != NULL; node = node->Next, index++)
        {
            if (_date.Month == node->Movie.ReleasedDate.Month)
                movies[index] = node->Movie;
        }
    }
    else if (_date.Date == 0 && _date.Month == 0 && _date.Year != 0)
    {
        for (Node* node = m_Head; node != NULL; node = node->Next)
        {
            if (_date.Year == node->Movie.ReleasedDate.Year)
                counter++;
        }

        movies = (Movie*)malloc(sizeof(Movie) * counter);
        for (Node* node = m_Head; node != NULL; node = node->Next, index++)
        {
            if (_date.Year == node->Movie.ReleasedDate.Year)
                movies[index] = node->Movie;
        }
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

void SaveStatus(const std::string& filepath)
{
    std::ofstream file(filepath);
    if (IsEmpty())
        file << "===================================";
    else
    {
        for (Node* node = m_Head; node != NULL; node = node->Next)
        {
            file << node->Movie.ID << "\n";
            file << node->Movie.Title << "\n";
            file << node->Movie.Rate << "\n";
            file << node->Movie.Price << "\n";
            file << node->Movie.Length << "\n";
            file << genreToString(node->Movie.Genre) << "\n";
            file << dateToString(node->Movie.ReleasedDate) << "\n";
            file << langToString(node->Movie.Lang);
            node == m_Tail ? file << "\n" : file << "\n===================================\n";
        }
    }
    file.close();

    std::cout << "[Success] The changes have been successfully applied.\n";
}

int CountByRate(float rate)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'CountByRate(...)'. The list is empty.");

    int total = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (node->Movie.Rate == rate)
            total++;
    }

    return total;
}

int CountByPrice(float price)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'CountByPrice(...)'. The list is empty.");

    int total = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (node->Movie.Price == price)
            total++;
    }

    return total;
}

int CountByLength(float length)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'CountByLength(...)'. The list is empty.");

    int total = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (node->Movie.Length == length)
            total++;
    }

    return total;
}

int CountByGenre(std::string genre)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'CountByGenre(...)'. The list is empty.");

    int total = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (node->Movie.Genre == stringToGenre(genre.c_str()))
            total++;
    }

    return total;
}

int CountByDate(std::string date)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'CountByDate(...)'. The list is empty.");

    int total = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (dateToString(node->Movie.ReleasedDate) == toUpper(date.c_str()))
            total++;
    }

    return total;
}

int CountByLang(std::string language)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'CountByLang(...)'. The list is empty.");

    int total = 0;
    for (Node* node = m_Head; node != NULL; node = node->Next)
    {
        if (langToString(node->Movie.Lang) == toUpper(language.c_str()))
            total++;
    }

    return total;
}

int GetSize()
{
    return m_Size;
}

void UpdateId(int oldID, int newID)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'UpdateId(...)'. The list is empty.");
    ASSERT(Contains(oldID), "[Error] MovieNotFoundException thrown from 'UpdateId(...)'. The movie is not in the list.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.ID != oldID; node = node->Next);
    node->Movie.ID = newID;

    std::cout << "[Success] The ID of the movie with Title \"" << GetById(oldID).Title
        << "\" is successfully updated by new ID of " << newID << ".\n";
}

void UpdateTitle(std::string oldTitle, std::string newTitle)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'UpdateTitle(...)'. The list is empty.");
    ASSERT(Contains(GetByTitle(oldTitle).ID), "[Error] MovieNotFoundException thrown from 'UpdateTitle(...)'. The movie is not in the list.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.Title != oldTitle; node = node->Next);
    node->Movie.Title = newTitle;

    std::cout << "[Success] The Title of the movie with Title \"" << oldTitle
        << "\" is successfully updated by new title of \"" << newTitle << "\".\n";
}

void UpdatePrice(int oldID, float newPrice)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'UpdatePrice(...)'. The list is empty.");
    ASSERT(Contains(oldID), "[Error] MovieNotFoundException thrown from 'UpdatePrice(...)'. The movie is not in the list.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.ID != oldID; node = node->Next);
    node->Movie.Price = newPrice;

    std::cout << "[Success] The Price of the movie with Title \"" << GetById(oldID).Title
        << "\" is successfully updated by new Price of " << newPrice << ".\n";
}

void UpdateLength(int oldID, float newLength)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'UpdateLength(...)'. The list is empty.");
    ASSERT(Contains(oldID), "[Error] MovieNotFoundException thrown from 'UpdateLength(...)'. The movie is not in the list.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.ID != oldID; node = node->Next);
    node->Movie.Length = newLength;

    std::cout << "[Success] The Time length of the movie with Title \"" << GetById(oldID).Title
        << "\" is successfully updated by new Length of " << newLength << ".\n";
}

void UpdateRate(int oldID, float newRate)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'UpdateRate(...)'. The list is empty.");
    ASSERT(Contains(oldID), "[Error] MovieNotFoundException thrown from 'UpdateRate(...)'. The movie is not in the list.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.ID != oldID; node = node->Next);
    node->Movie.Rate = newRate;

    std::cout << "[Success] The Rating of the movie with Title \"" << GetById(oldID).Title
        << "\" is successfully updated by new Rate of " << newRate << ".\n";
}

void UpdateGenre(int oldID, std::string newGenre)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'UpdateById(...)'. The list is empty.");
    ASSERT(Contains(oldID), "[Error] MovieNotFoundException thrown from 'UpdateById(...)'. The movie is not in the list.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.ID != oldID; node = node->Next);
    node->Movie.Genre = stringToGenre(newGenre.c_str());

    std::cout << "[Success] The Genre of the movie with Title \"" << GetById(oldID).Title
        << "\" is successfully updated by new Genre of " << newGenre << ".\n";
}

void UpdateLang(int oldID, std::string newLang)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'UpdateLang(...)'. The list is empty.");
    ASSERT(Contains(oldID), "[Error] MovieNotFoundException thrown from 'UpdateLang(...)'. The movie is not in the list.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.ID != oldID; node = node->Next);
    node->Movie.Lang = stringToLang(newLang.c_str());

    std::cout << "[Success] The Language of the movie with Title \"" << GetById(oldID).Title
        << "\" is successfully updated by new Language of " << newLang << ".\n";
}

void UpdateDate(int oldID, std::string newDate)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'UpdateDate(...)'. The list is empty.");
    ASSERT(Contains(oldID), "[Error] MovieNotFoundException thrown from 'UpdateDate(...)'. The movie is not in the list.");

    Node* node = m_Head;
    for (; node != NULL && node->Movie.ID != oldID; node = node->Next);
    node->Movie.ReleasedDate = stringToDate(newDate);

    std::cout << "[Success] The Date of the movie with Title \"" << GetById(oldID).Title
        << "\" is successfully updated by new Date of " << newDate << ".\n";
}

void SortByID()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'SortById()'. The list is empty.");

    if (m_Size > 1)
    {
        Node* trav = m_Head->Next;
        for (; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && tempMovie.ID < tempNode->Movie.ID)
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
    }
}

void SortByTitle()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'SortByTitle()'. The list is empty.");

    if (m_Size > 1)
    {
        Node* trav = m_Head->Next;
        for (; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && tempMovie.Title < tempNode->Movie.Title)
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
    }
}

void SortByPrice()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'SortByPrice()'. The list is empty.");

    if (m_Size > 1)
    {
        Node* trav = m_Head->Next;
        for (; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && tempMovie.Price < tempNode->Movie.Price)
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
    }
}

void SortByLength()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'SortByLength()'. The list is empty.");

    if (m_Size > 1)
    {
        Node* trav = m_Head->Next;
        for (; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && tempMovie.Length < tempNode->Movie.Length)
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
    }
}

void SortByRate()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'SortByRate()'. The list is empty.");

    if (m_Size > 1)
    {
        Node* trav = m_Head->Next;
        for (; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && tempMovie.Rate < tempNode->Movie.Rate)
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
    }
}

void SortByGenre()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'SortByGenre()'. The list is empty.");

    if (m_Size > 1)
    {
        Node* trav = m_Head->Next;
        for (; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && genreToString(tempMovie.Genre) < genreToString(tempNode->Movie.Genre))
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
    }
}

void SortByLang()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'SortByLang()'. The list is empty.");

    if (m_Size > 1)
    {
        Node* trav = m_Head->Next;
        for (; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && langToString(tempMovie.Lang) < langToString(tempNode->Movie.Lang))
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
    }
}

void SortByDate()
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'SortByDate()'. The list is empty.");

    if (m_Size > 1)
    {
        for (Node* trav = m_Head->Next; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && tempMovie.ReleasedDate.Year < tempNode->Movie.ReleasedDate.Year)
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
        for (Node* trav = m_Head->Next; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && tempMovie.ReleasedDate.Month < tempNode->Movie.ReleasedDate.Month)
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
        for (Node* trav = m_Head->Next; trav != NULL; trav = trav->Next)
        {
            Node* tempNode = trav->Prev;
            Movie tempMovie = trav->Movie;

            while (tempNode != NULL && tempMovie.ReleasedDate.Date < tempNode->Movie.ReleasedDate.Date)
            {
                tempNode->Next->Movie = tempNode->Movie;
                tempNode = tempNode->Prev;
            }
            tempNode->Next->Movie = tempMovie;
        }
    }
}

void TopByID(size_t size)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'TopByID()'. The list is empty.");
    ASSERT(size <= size_t(m_Size), "[Error] IndexOutOfBoundException thrown from 'TopByID()'. You entered index out of the size of the list.");

    SortByID();
    int i = 0;
    for (Node* node = m_Head; i < int(size); node = node->Next, i++)
        printMovie(node->Movie);
}

void TopByTitle(size_t size)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'TopByTitle()'. The list is empty.");
    ASSERT(size <= size_t(m_Size), "[Error] IndexOutOfBoundException thrown from 'TopByTitle()'. You entered index out of the size of the list.");

    SortByTitle();
    int i = 0;
    for (Node* node = m_Head; i < int(size); node = node->Next, i++)
        printMovie(node->Movie);
}

void TopByPrice(size_t size)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'TopByPrice()'. The list is empty.");
    ASSERT(size <= size_t(m_Size), "[Error] IndexOutOfBoundException thrown from 'TopByPrice()'. You entered index out of the size of the list.");

    SortByPrice();
    int i = 0;
    for (Node* node = m_Head; i < int(size); node = node->Next, i++)
        printMovie(node->Movie);
}

void TopByRate(size_t size)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'TopByRate()'. The list is empty.");
    ASSERT(size <= size_t(m_Size), "[Error] IndexOutOfBoundException thrown from 'TopByRate()'. You entered index out of the size of the list.");

    SortByRate();
    int i = 0;
    for (Node* node = m_Head; i < int(size); node = node->Next, i++)
        printMovie(node->Movie);
}

void TopByDate(size_t size)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'TopByDate()'. The list is empty.");
    ASSERT(size <= size_t(m_Size), "[Error] IndexOutOfBoundException thrown from 'TopByDate()'. You entered index out of the size of the list.");

    SortByDate();
    int i = 0;
    for (Node* node = m_Head; i < int(size); node = node->Next, i++)
        printMovie(node->Movie);
}

void DisplayForward()
{
    if (IsEmpty())
        std::cout << "[Error]: There is no movie to show you.\n";
    else
    {
        std::cout << "YOU ARE DISPLAYING ALL THE MOVIES FORWARD\n";
        for (Node* node = m_Head; node != NULL; node = node->Next)
            printMovie(node->Movie);
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
            printMovie(node->Movie);
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
    return IndexOf(movie.ID);
}

bool Contains(int movieID)
{
    ASSERT(!IsEmpty(), "[Error] IllegalAccessException thrown from 'Contains(...)'. The list is empty.");
    return (IndexOf(movieID) != -1);
}

void printMovie(Movie movie)
{
    std::cout << "------------------------------------------------------------------------------\n";
    std::cout << "ID: " << movie.ID << "\n";
    std::cout << "Title: " << movie.Title.c_str() << "\n";
    std::cout << "Rate: " << movie.Rate << " / 10\n";
    std::cout << "Price: $" << movie.Price << "\n";
    std::cout << "Length: " << movie.Length << " Hr\n";
    std::cout << "Genre: " << genreToString(movie.Genre).c_str() << "\n";
    std::cout << "Released Date: " << dateToString(movie.ReleasedDate).c_str() << "\n";
    std::cout << "Language: " << langToString(movie.Lang).c_str() << "\n";
    std::cout << "------------------------------------------------------------------------------\n";
}

std::string toUpper(const char* string)
{
    char* str = (char*)malloc(sizeof(string));
    for (int i = 0; i < int(sizeof(string)); i++)
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
