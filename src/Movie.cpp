#include "Core.h"

void Movie::AddMovieFirst(std::string filepath)
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

            Node* node = new Node();
            node->Movie->ID = std::stoi(fileContent[0]);
            node->Movie->Title = fileContent[1];
            node->Movie->Rate = std::stof(fileContent[2]);
            node->Movie->Price = std::stof(fileContent[3]);
            node->Movie->Length = std::stof(fileContent[4]);
            node->Movie->Genre = stringToGenre(fileContent[5].c_str());
            node->Movie->ReleasedDate = stringToDate(fileContent[6].c_str());
            node->Movie->Lang = stringToLang(fileContent[7].c_str());
            node->Prev = NULL;

            if (IsMovieEmpty())
                m_Head = m_Tail = node;
            else
            {
                node->Next = m_Head;
                m_Head->Prev = node;
                m_Head = node;
            }

            i = 0;
            count++;
        }
    }

    print("[Info] %d movies are successfully added.", count);
}

void Movie::AddMovieLast(MovieEntity* movie)
{

}

void Movie::InsertMovieAtIndex(int index, MovieEntity* movie)
{

}

void Movie::InsertMovieById(MovieEntity* movie, bool before, int ID)
{

}

void Movie::InsertMovieByTitle(MovieEntity* movie, bool before, std::string title)
{

}

void Movie::RemoveMovieFirst()
{

}

void Movie::RemoveMovieLast()
{

}

void Movie::RemoveMovieById(int ID)
{

}

void Movie::RemoveMovieByTitle(std::string title)
{

}

void Movie::RemoveMovieByIndex(int index)
{

}

void Movie::RemoveMovie(MovieEntity movie)
{

}

void Movie::RemoveMovieByLang(Language lang)
{

}

void Movie::RemoveMovieByGenre(MovieType genre)
{

}

void Movie::RemoveMovieByDate(Date releasedDate)
{

}

Movie Movie::GetMovieById(int ID)
{

}

Movie Movie::GetMovieByTitle(std::string title)
{

}

Movie Movie::GetMovieByIndex(int index)
{

}

Movie* Movie::GetMoviesByLang(Language lang)
{

}

Movie* Movie::GetMoviesByGenre(MovieType genre, int top)
{

}

Movie* Movie::GetMoviesByDate(Date releasedDate, int top)
{

}

Movie* Movie::GetMoviesByPrice(float price, int top)
{

}

Movie* Movie::GetMoviesByRate(float rate, int top)
{

}

Movie* Movie::GetMoviesByLength(float length, int top)
{

}

void Movie::UpdateMovieById(int ID, MovieEntity movie)
{

}

void Movie::UpdateMovieByTitle(std::string title, MovieEntity movie)
{

}

void Movie::DisplayMovieForward()
{
    if (IsMovieEmpty())
        print("[Error]: There is no movie to show you.");
    else
    {
        print("YOU ARE DISPLAYING ALL THE MOVIES FORWARD");
        for (Node* node = m_Head; node != NULL; node = node->Next)
            printNode(node)
    }
}

void Movie::DisplayMovieBackward()
{
    if (IsMovieEmpty())
        print("[Error]: There is no movie to show you.");
    else
    {
        print("YOU ARE DISPLAYING ALL THE MOVIES BACKWARD");
        for (Node* node = m_Tail; node != NULL; node = node->Prev)
            printNode(node);
    }
}

void Movie::printNode(Node* node)
{
    print("------------------------------------------------------------------------------");
    print("Title: %s", node->Movie->Title.c_str());
    print("Rate: %.1f", node->Movie->Rate);
    print("Price: %.2f", node->Movie->Price);
    print("Length: %.2f", node->Movie->Length);
    print("Genre: %s", genreToString(node->Movie->Genre).c_str());
    print("Released Date: %s", dateToString(node->Movie->ReleasedDate).c_str());
    print("Language: %s", langToString(node->Movie->Language).c_str());
    print("------------------------------------------------------------------------------");
}

inline bool Movie::IsMovieEmpty()
{
    return (m_Head == NULL);
}

std::string Movie::toUpper(const char* string)
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


Date Movie::stringToDate(std::string string)
{
    Date date;
    date.Month = std::stoi(string.substr(0, 2));
    date.Date = std::stoi(string.substr(3, 5));
    date.Year = std::stoi(string.substr(6, 10));
    return date;
}

MovieType Movie::stringToGenre(const char* string)
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

Language Movie::stringToLang(const char* string)
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

}

std::string genreToString(MovieType genre)
{

}

std::string langToString(Language lang)
{

}
