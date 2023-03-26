#include "Program.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Movie.h"
#include "Core.h"

bool g_IsRunning = true;

void Main()
{
    while (g_IsRunning)
    {
        Menu();
    }
}

void Menu()
{
program:
    int choice;
    system("cls");
    std::cout << "---------------------------------------------------------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "---------- WELCOME TO MOVIE MANAGEMENT SYSTEM -----------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "---------------------------------------------------------\n\n";

    std::cout << "---------------------------------------------------------\n";
    std::cout << "-------------------- PROGRAM MENU -----------------------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "--------- (1).  Load Movies from the data center --------\n";
    std::cout << "--------- (2).  Add New Movies                   --------\n";
    std::cout << "--------- (3).  Remove Movies                    --------\n";
    std::cout << "--------- (4).  Update Movies                    --------\n";
    std::cout << "--------- (5).  Sort Movies                      --------\n";
    std::cout << "--------- (6).  Display All Movies               --------\n";
    std::cout << "--------- (7).  Other Functionalities            --------\n";
    std::cout << "--------- (8).  Help                             --------\n";
    std::cout << "--------- (9).  About The Developers             --------\n";
    std::cout << "--------- (10). Exit The Program                ---------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "-- If you are new to our program, we highly recommend ---\n";
    std::cout << "-- you to start with the help section to understand   ---\n";
    std::cout << "-- more about the program.                            ---\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << ">> ";
    std::cin >> choice;

    if (choice == 1)
    {
        std::ifstream file("modified-movies.txt");
        if (file.is_open())
        {
            char choice;
            std::cout << "Do you want to load the previously saved (s) file or the default (*) one (s -> saved, * -> default): ";
            std::cin >> choice;

            if (choice == 's' || choice == 'S')
                LoadDatabase("modified-movies.txt");
            else LoadDatabase("movies.txt");
        }
        else LoadDatabase("movies.txt");
        file.close();
    }
    else if (choice == 2)
        AddMovies();
    else if (choice == 3)
        RemoveMovies();
    else if (choice == 4)
        UpdateMovies();
    else if (choice == 5)
        SortMovies();
    else if (choice == 6)
        DisplayMovies();
    else if (choice == 7)
        OtherFunctionalities();
    else if (choice == 8)
        Help();
    else if (choice == 9)
        About();
    else if (choice == 10)
    {
        system("cls");
        char isGoingToSave;
        std::cout << "[Info] I am shutting down, do you want to save your progress (y/N): ";
        std::cin >> isGoingToSave;
        if (isGoingToSave== 'Y' || isGoingToSave== 'y')
        {
            SaveStatus("modified-movies.txt");
            std::cout << "[Success] The status saved successfully, Good Bye :)\n";
        }
        else std::cout << "[Info] Good Bye :)\n";
        g_IsRunning = false;
        system("pause");
    }
    else
    {
        std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
        system("pause");
        goto program;
    }
}

void LoadDatabase(const char* filepath)
{
    std::cout << "[Info] Loading data from the data source ...\n";
    AddFirst(filepath);

    std::cout << "[Success] The data is successfully loaded.\n\n";
    DisplayForward();
    system("pause");
    Menu();
}

void AddMovies()
{
recieveMovie:
    system("cls");
    Movie movie;
    char title[25], genre[25], lang[25], date[25];

    std::cout << "Movie\n";
    std::cout << "\tID: ";
    std::cin >> movie.ID;
    std::cout << "\tTitle: ";
    std::cin >> title;
    std::cout << "\tRating: ";
    std::cin >> movie.Rate;
    std::cout << "\tPrice: ";
    std::cin >> movie.Price;
    std::cout << "\tLength: ";
    std::cin >> movie.Length;
    std::cout << "\tGenre (Movie Type): ";
    std::cin >> genre;
    std::cout << "\tDate: ";
    std::cin >> date;
    std::cout << "\tLanguage: ";
    std::cin >> lang;

    movie.Title = std::string(title);
    movie.Genre = stringToGenre(genre);
    movie.ReleasedDate = stringToDate(std::string(date));
    movie.Lang = stringToLang(lang);

    VALIDATE(movie.ID > 0, recieveMovie, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");
    VALIDATE(movie.Rate >= 0.f && movie.Rate <= 10.f , recieveMovie, "[Warning] Invalid Rating. It should be between 0.0 and 10.0. . Please re-enter the information correctly!");
    VALIDATE(movie.Price >= 0.f, recieveMovie, "[Warning] Invalid Price. Price can not be negative. Please re-enter the information correctly!");
    VALIDATE(movie.Length > 0.f, recieveMovie, "[Warning] Invalid Movie Length. It should be > 0. Please re-enter the information correctly!");
    VALIDATE(movie.ReleasedDate.Month >= 1 && movie.ReleasedDate.Month <= 12, recieveMovie, "[Warning] Invalid Date. Month should be between 1 and 12. Please re-enter the information correctly!");
    VALIDATE(movie.ReleasedDate.Date >= 1 && movie.ReleasedDate.Date <= 30, recieveMovie, "[Warning] Invalid Date. Date should be between 1 and 30. Please re-enter the information correctly!");
    VALIDATE(movie.ReleasedDate.Year >= 1, recieveMovie, "[Warning] Invalid Date. Year should be > 0. Please re-enter the information correctly!");
    VALIDATE(movie.Lang == Language::AMHARIC ||
        movie.Lang == Language::ARABIC ||
        movie.Lang == Language::CHINESE ||
        movie.Lang == Language::KOREAN ||
        movie.Lang == Language::ENGLISH ||
        movie.Lang == Language::FRENCH ||
        movie.Lang == Language::HINDU ||
        movie.Lang == Language::SPANISH
        , recieveMovie, "[Warning] Invalid Language. The Languages should be in the validated list of languages. Please re-enter the information correctly!");
    VALIDATE(movie.Genre == MovieType::ACTION ||
        movie.Genre == MovieType::ADVENTURE ||
        movie.Genre == MovieType::COMMEDY ||
        movie.Genre == MovieType::DRAMA ||
        movie.Genre == MovieType::FANTANSY ||
        movie.Genre == MovieType::HORROR ||
        movie.Genre == MovieType::MYSTERY ||
        movie.Genre == MovieType::ROMANCE ||
        movie.Genre == MovieType::SCIFI ||
        movie.Genre == MovieType::SPORTS ||
        movie.Genre == MovieType::THRILLER ||
        movie.Genre == MovieType::WESTERN
        , recieveMovie, "[Warning] Invalid Genre. The genre should be in the validated movie type. Please re-enter the information correctly!");

addMovies:
    int choice;
    std::cout << "\n1. Insert at the last.\n";
    std::cout << "2. Insert at the middle.\n";
    std::cout << ">> ";
    std::cin >> choice;

    if (choice == 1)
    {
        AddLast(movie);
    }
    else if (choice == 2)
    {
    chooseKeyType:
        int keyType;
        char c;
        std::cout << "\nNow choose the type of key\n";
        std::cout << "\t1. By its ID\n";
        std::cout << "\t2. By its Title\n";
        std::cout << "\t3. By its Position\n";
        std::cout << ">> ";
        std::cin >> keyType;
        std::cout << "\nDo you want to insert the new movie before/after? ";
        std::cin >> c;

        if (keyType == 1)
        {
            int id;
        recieveID:
            std::cout << "\nEnter the ID number: ";
            std::cin >> id;

            VALIDATE(id > 0, recieveID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");
            InsertById(movie, (c == 'b' || c == 'B'), id);
        }
        else if (keyType == 2)
        {
            char title[25];
            std::cout << "\nEnter the Title: ";
            std::cin >> title;

            InsertByTitle(movie, (c == 'b' || c == 'B'), std::string(title));
        }
        else if (keyType == 3)
        {
            int position;
        recievePos:
            std::cout << "\nEnter the Position of the movie: ";
            std::cin >> position;

            VALIDATE(position > 0, recievePos, "[Warning] Invalid Position. It should be > 0. Please re-enter the information correctly!");
            InsertAtIndex(position - 1, movie);
        }
        else
        {
            std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
            system("pause");
            goto chooseKeyType;
        }
    }
    else
    {
        std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
        system("pause");
        goto addMovies;
    }
    system("pause");
    Menu();
}

void RemoveMovies()
{
    int choice;
removeMovies:
    system("cls");
    std::cout << "Do you want to delete\n";
    std::cout << "\t1. The first movie.\n";
    std::cout << "\t2. The last movie.\n";
    std::cout << "\t3. The movie by its attributes.\n";
    std::cin >> choice;

    if (choice == 1)
        RemoveFirst();
    else if (choice == 2)
        RemoveLast();
    else if (choice == 3)
    {
    removeByKey:
        int keyType;
        std::cout << "\nDelete movie\n";
        std::cout << "\t1. By its ID\n";
        std::cout << "\t2. By its Title\n";
        std::cout << "\t3. By its Position\n";
        std::cout << "\t4. By its Language\n";
        std::cout << "\t5. By its Date\n";
        std::cout << "\t6. By its Genre\n";
        std::cout << "\t7. By its Minimum value\n";
        std::cout << "\t8. By its Maximum value\n";
        std::cin >> keyType;

        if (keyType == 1)
        {
        removeByID:
            int id;
            std::cout << "Enter the id of the movie: ";
            std::cin >> id;

            VALIDATE(id > 0, removeByID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");
            RemoveById(id);
        }
        else if (keyType == 2)
        {
            char title[25];
            std::cout << "Enter the title of the movie: ";
            std::cin >> title;

            RemoveByTitle(title);
        }
        else if (keyType == 3)
        {
        removeByPosition:
            int position;
            std::cout << "Enter the position of the movie (E.g: 1 or 4 or 10): ";
            std::cin >> position;

            VALIDATE(position > 0, removeByPosition, "[Warning] Invalid Position. It should be > 0. Please re-enter the information correctly!");
            RemoveByIndex(position - 1);
        }
        else if (keyType == 4)
        {
            char lang[25];
            std::cout << "Enter the language of the movies (E.g: amharic, french, english): ";
            std::cin >> lang;

            RemoveByLang(std::string(lang));
        }
        else if (keyType == 5)
        {
        removeByDate:
            char date[25];
            std::cout << "Enter the date of the movies (E.g: mm/dd/yyyy format): ";
            std::cin >> date;

            Date tempDate = stringToDate(date);

            VALIDATE(tempDate.Month >= 1 && tempDate.Month <= 12, removeByDate, "[Warning] Invalid Date. Month should be between 1 and 12. Please re-enter the information correctly!");
            VALIDATE(tempDate.Date >= 1 && tempDate.Date <= 30, removeByDate, "[Warning] Invalid Date. Date should be between 1 and 30. Please re-enter the information correctly!");
            VALIDATE(tempDate.Year >= 1, removeByDate, "[Warning] Invalid Date. Year should be at least > 0. Please re-enter the information correctly!");

            RemoveByDate(std::string(date));
        }
        else if (keyType == 6)
        {
            char genre[25];
            std::cout << "Enter the genre of the movies (E.g: action, horror, drama): ";
            std::cin >> genre;

            RemoveByGenre(std::string(genre));
        }
        else if (keyType == 7)
        {
        removeByMin:
            int c;
            std::cout << "\nDo you want to delete\n";
            std::cout << "\t1. Movie with minimum price\n";
            std::cout << "\t2. Movie with minimum rating\n";
            std::cin >> c;

            if (c == 1)
                RemoveByMinPrice();
            else if (c == 2)
                RemoveByMinRate();
            else
            {
                std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
                system("pause");
                goto removeByMin;
            }
            system("pause");
        }
        else if (keyType == 8)
        {
        removeByMax:
            int c;
            std::cout << "\nDo you want to delete\n";
            std::cout << "\t1. Movie with maximum price\n";
            std::cout << "\t2. Movie with maximum rating\n";
            std::cin >> c;

            if (c == 1)
                RemoveByMaxPrice();
            else if (c == 2)
                RemoveByMaxRate();
            else
            {
                std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
                system("pause");
                goto removeByMax;
            }
            system("pause");
        }
        else
        {
            std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
            system("pause");
            goto removeByKey;
        }
        system("pause");
    }
    else
    {
        std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
        system("pause");
        goto removeMovies;
    }
    system("pause");
}

void UpdateMovies()
{
updateMovies:
    system("cls");
    int choice;
    std::cout << "Do you want to update movie\n";
    std::cout << "\t1. By its ID\n";
    std::cout << "\t2. By its Title\n";
    std::cout << "\t3. By its Price\n";
    std::cout << "\t4. By its Length\n";
    std::cout << "\t5. By its Rating\n";
    std::cout << "\t6. By its Genre\n";
    std::cout << "\t7. By its Language\n";
    std::cout << "\t8. By its Date\n";
    std::cin >> choice;

    if (choice == 1)
    {
        int oldID, newID;
    updateByIDRecieveOldID:
        std::cout << "\nEnter the ID of the movie to be updated: ";
        std::cin >> oldID;
        VALIDATE(oldID > 0, updateByIDRecieveOldID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");

    updateByIDRecieveNewID:
        std::cout << "Enter the new ID of the movie: ";
        std::cin >> newID;
        VALIDATE(newID > 0, updateByIDRecieveNewID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");

        UpdateId(oldID, newID);
    }
    else if (choice == 2)
    {
        char oldTitle[25], newTitle[25];
        std::cout << "\nEnter the Title of the movie to be updated: ";
        std::cin >> oldTitle;
        std::cout << "\nEnter the new Title of the movie: ";
        std::cin >> newTitle;

        UpdateTitle(std::string(oldTitle), std::string(newTitle));
    }
    else if (choice == 3)
    {
        float newPrice;
        int oldID;
    updateByPriceRecieveID:
        std::cout << "\nEnter the movie id to be updated: ";
        std::cin >> oldID;
        VALIDATE(oldID > 0, updateByPriceRecieveID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");

    updateByPriceRecievePrice:
        std::cout << "Enter the new price of the movie: ";
        std::cin >> newPrice;
        VALIDATE(newPrice >= 0.f, updateByPriceRecievePrice, "[Warning] Invalid Price. Price can not be negative. Please re-enter the information correctly!");

        UpdatePrice(oldID, newPrice);
    }
    else if (choice == 4)
    {
        float newLength;
        int oldID;
    updateByLengthRecieveID:
        std::cout << "\nEnter the movie id to be updated: ";
        std::cin >> oldID;
        VALIDATE(oldID > 0, updateByLengthRecieveID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");

    updateByLengthRecieveLength:
        std::cout << "Enter the new length of the movie: ";
        std::cin >> newLength;
        VALIDATE(newLength > 0.f, updateByLengthRecieveLength, "[Warning] Invalid Length. Length should be > 0. Please re-enter the information correctly!");

        UpdateLength(oldID, newLength);
    }
    else if (choice == 5)
    {
        float newRating;
        int oldID;
    updateByRatingRecieveID:
        std::cout << "\nEnter the movie id to be updated: ";
        std::cin >> oldID;
        VALIDATE(oldID > 0, updateByRatingRecieveID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");

    updateByRatingRecieveRating:
        std::cout << "Enter the new Rating of the movie: ";
        std::cin >> newRating;
        VALIDATE(newRating >= 0.f && newRating <= 10.f , updateByRatingRecieveRating, "[Warning] Invalid Rating. It should be between 0.0 and 10.0. . Please re-enter the information correctly!");

        UpdateRate(oldID, newRating);
    }
    else if (choice == 6)
    {
        char newGenre[25];
        int oldID;
    updateByGenreRecieveID:
        std::cout << "\nEnter the movie id to be updated: ";
        std::cin >> oldID;
        VALIDATE(oldID > 0, updateByGenreRecieveID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");

        std::cout << "Enter the new Genre of the movie: ";
        std::cin >> newGenre;

        UpdateGenre(oldID, std::string(newGenre));
    }
    else if (choice == 7)
    {
        char newLang[25];
        int oldID;
    updateByLangRecieveID:
        std::cout << "\nEnter the movie id to be updated: ";
        std::cin >> oldID;
        VALIDATE(oldID > 0, updateByLangRecieveID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");

        std::cout << "Enter the new Language of the movie: ";
        std::cin >> newLang;

        UpdateLang(oldID, std::string(newLang));
    }
    else if (choice == 8)
    {
        char newDate[25];
        int oldID;
    updateByDateRecieveID:
        std::cout << "\nEnter the movie id to be updated: ";
        std::cin >> oldID;
        VALIDATE(oldID > 0, updateByDateRecieveID, "[Warning] Invalid ID. It should be > 0. Please re-enter the information correctly!");

    updateByDateRecieveDate:
        std::cout << "Enter the new Date of the movie: ";
        std::cin >> newDate;

        Date tempDate = stringToDate(newDate);

        VALIDATE(tempDate.Month >= 1 && tempDate.Month <= 12, updateByDateRecieveDate, "[Warning] Invalid Date. Month should be between 1 and 12. Please re-enter the information correctly!");
        VALIDATE(tempDate.Date >= 1 && tempDate.Date <= 30, updateByDateRecieveDate, "[Warning] Invalid Date. Date should be between 1 and 30. Please re-enter the information correctly!");
        VALIDATE(tempDate.Year >= 1, updateByDateRecieveDate, "[Warning] Invalid Date. Year should be at least > 0. Please re-enter the information correctly!");

        UpdateDate(oldID, std::string(newDate));
    }
    else
    {
        std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
        system("pause");
        goto updateMovies;
    }
    system("pause");
}

void SortMovies()
{
sortMovies:
    system("cls");
    int choice;
    std::cout << "Sort Movies by their\n";
    std::cout << "\t1. ID\n";
    std::cout << "\t2. Title\n";
    std::cout << "\t3. Price\n";
    std::cout << "\t4. Length\n";
    std::cout << "\t5. Rating\n";
    std::cout << "\t6. Genre\n";
    std::cout << "\t7. Language\n";
    std::cout << "\t8. Date\n";
    std::cin >> choice;

    if (choice == 1)
    {
        InsertionSort("id");
        DisplayForward();
        system("pause");
    }
    else if (choice == 2)
    {
        InsertionSort("title");
        DisplayForward();
        system("pause");
    }
    else if (choice == 3)
    {
        InsertionSort("price");
        DisplayForward();
        system("pause");
    }
    else if (choice == 4)
    {
        InsertionSort("length");
        DisplayForward();
        system("pause");
    }
    else if (choice == 5)
    {
        InsertionSort("rate");
        DisplayForward();
        system("pause");
    }
    else if (choice == 6)
    {
        InsertionSort("genre");
        DisplayForward();
        system("pause");
    }
    else if (choice == 7)
    {
        InsertionSort("language");
        DisplayForward();
        system("pause");
    }
    else if (choice == 8)
    {
        InsertionSort("date");
        DisplayForward();
        system("pause");
    }
    else
    {
        std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
        system("pause");
        goto sortMovies;
    }
}

void DisplayMovies()
{
displayMovies:
    int choice;
    std::cout << "Do you want to display the movies\n";
    std::cout << "\t1. Forward\n";
    std::cout << "\t2. Backward\n";
    std::cin >> choice;

    if (choice == 1)
    {
        DisplayForward();
        system("pause");
    }
    else if (choice == 2)
    {
        DisplayBackward();
        system("pause");
    }
    else
    {
        std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
        system("pause");
        goto displayMovies;
    }
}

void OtherFunctionalities()
{
    system("cls");
otherFunctionalities:
    int choice;
    std::cout << "1. To display top 'n' number of movies.\n";
    std::cout << "2. To search movies.\n";
    std::cout << "3. To count movies.\n";
    std::cout << "4. To save your status.\n";
}

void Help()
{
    system("cls");
    std::ifstream file("help-desk.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
            std::cout << line << "\n";
        std::cout << "\n\n";
    }
    else std::cout << "[Error] the \"help-desk.txt\" file doesn't exist in your directory.\n";
    file.close();
    system("pause");
}

void About()
{
    system("cls");
    std::cout << " ____________________________________________________________________________\n";
    std::cout << "|                       THIS PROGRAM IS DEVELOPED BY                         |\n";
    std::cout << "|____________________________________________________________________________|\n";
    std::cout << "|          NAME            |     ID        |             E-MAIL              |\n";
    std::cout << "|--------------------------|---------------|---------------------------------|\n";
    std::cout << "|  1. Anduamlak Yalewlet   |  BDU1404555   |     anduamlak2014@gmail.com     |\n";
    std::cout << "|--------------------------|---------------|---------------------------------|\n";
    std::cout << "|  2. Eyob Zekarias        |  BDU1404462   |     eyobzekarias23@gmail.com    |\n";
    std::cout << "|--------------------------|---------------|---------------------------------|\n";
    std::cout << "|  3. Henok Eshetu         |  BDU1410525   |     henokesh95@gmail.com        |\n";
    std::cout << "|__________________________|_______________|_________________________________|\n";
    system("pause");
}
