#include "Program.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include "Movie.h"

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
    std::string choice;
    system("cls");
    std::cout << "---------------------------------------------------------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "---------- WELCOME TO MOVIE MANAGEMENT SYSTEM -----------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "---------------------------------------------------------\n\n";
    
    std::cout << "---------------------------------------------------------\n";
    std::cout << "-------------------- PROGRAM MENU -----------------------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "--------- (1). Load Movies from the data center ---------\n";
    std::cout << "--------- (2). Add New Movies                   ---------\n";
    std::cout << "--------- (3). Remove Movies                    ---------\n";
    std::cout << "--------- (4). Update Movies                    ---------\n";
    std::cout << "--------- (5). Sort Movies                      ---------\n";
    std::cout << "--------- (6). Other Functionalities            ---------\n";
    std::cout << "--------- (7). Help                             ---------\n";
    std::cout << "--------- (8). About                            ---------\n";
    std::cout << "--------- (9). Exit The Program                 ---------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << ">> ";
    std::getline(std::cin, choice);

    if (choice == "1")
        LoadDatabase("movies.txt");
    else if (choice == "2")
        AddMovies();
    else if (choice == "3")
        RemoveMovies();
    else if (choice == "4")
        UpdateMovies();
    else if (choice == "5")
        SortMovies();
    else if (choice == "6")
        OtherFunctionalities();
    else if (choice == "7")
        Help();
    else if (choice == "8")
        About();
    else if (choice == "9")
    {
        system("cls");
        std::string isGoingToSave;
        std::cout << "[Info] I am shutting down, do you want to save your progress (y/N): ";
        std::getline(std::cin, isGoingToSave);
        if (toUpper(isGoingToSave) == "Y")
        {
            // TODO: to be save here
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

void LoadDatabase(const std::string& filepath)
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
addMovies:
    system("cls");
    std::string choice;
    std::cout << "1. Insert at the last.\n";
    std::cout << "2. Insert at the middle.\n";
    std::cout << ">> ";
    std::getline(std::cin, choice);

    if (choice == "1")
    {
        size_t size;
        std::cout << "How Many Movies do you want to add? ";
        std::cin >> size;
        for (int i = 0; i < size; i++)
        {
            Movie movie;
            std::string genre, lang, date;

            std::cout << "\nMovie\n";
            std::cout << "\tID: ";
            std::cin >> movie.ID;
            std::cout << "\tTitle: ";
            std::getline(std::cin, movie.Title);
            std::cout << "\tRating: ";
            std::cin >> movie.Rate;
            std::cout << "\tPrice: ";
            std::cin >> movie.Price;
            std::cout << "\tLength: ";
            std::cin >> movie.Length;
            std::cout << "\tGenre (Movie Type): ";
            std::getline(std::cin, genre);
            movie.Genre = stringToGenre(genre);

            std::cout << "\tDate: ";
            std::getline(std::cin, date);
            movie.ReleasedDate = stringToDate(date);

            std::cout << "\tLanguage: ";
            std::getline(std::cin, lang);
            movie.Lang = stringToLang(lang);

            AddLast(movie);
        }

        std::cout << "[Success] You have successfully added " << size << " movies.\n";
    }
    else if (choice == "2")
    {
        Movie movie;
        std::string genre, lang, date;
    recieveMovie:
        system("cls");
        std::cout << "\nMovie\n";
        std::cout << "\tID: ";
        std::cin >> movie.ID;
        std::cout << "\tTitle: ";
        std::getline(std::cin, movie.Title);
        std::cout << "\tRating: ";
        std::cin >> movie.Rate;
        std::cout << "\tPrice: ";
        std::cin >> movie.Price;
        std::cout << "\tLength: ";
        std::cin >> movie.Length;
        std::cout << "\tGenre (Movie Type): ";
        std::getline(std::cin, genre);
        movie.Genre = stringToGenre(genre);
        std::cout << "\tDate: ";
        std::getline(std::cin, date);
        movie.ReleasedDate = stringToDate(date);
        std::cout << "\tLanguage: ";
        std::getline(std::cin, lang);
        movie.Lang = stringToLang(lang);
        
        ASSERT(movie.ID > 0, recieveMovie, "[Warning] Invalid ID. It should be > 0.");
        ASSERT(movie.Rate >= 0.f && movie.Rate <= 10.f , recieveMovie, "[Warning] Invalid Rating. It should be between 0.0 and 10.0");
        ASSERT(id > 0, recieveMovie, "[Warning]");
        ASSERT(id > 0, recieveMovie, "[Warning]");
        ASSERT(id > 0, recieveMovie, "[Warning]");

        chooseKeyType:
        std::string keyType;
        std::cout << "\nNow choose the type of key\n";
        std::cout << "\t1. By its ID\n";
        std::cout << "\t2. By its Title\n";
        std::cout << "\t3. By its Position\n";
        std::cout << ">> ";
        std::getline(std::cin, keyType);

        if (choice == "1")
        {

        }
        else if (choice == "2")
        {

        }
        else if (choice == "3")
        {

        }
        else
        {

        }

        std::cout << "Do you want to insert the new movie before/after the key? (b/*) ";
    }
    else
    {
        std::cout << "[Warning] Invalid data passed to the program. Please re-enter the validated choice!\n";
        system("pause");
        goto addFirst;
    }
    system("pause");
    Menu();
}

void RemoveMovies()
{
    
}

void UpdateMovies()
{

}

void SortMovies()
{

}

void DisplayMovies()
{

}

void OtherFunctionalities()
{

}
