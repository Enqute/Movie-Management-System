#include <iostream>
#include <fstream>
#include "Program.h"

int main()
{
    std::ifstream movies("movies.txt"), help("help-desk.txt");
    if (movies.is_open() && help.is_open())
    {
        movies.close();
        help.close();
        Main();
    }
    else
    {
        movies.close();
        help.close();

        char choice;
        std::cout << "[Critical] Some system files are missed. The program may not do tasks as expected!\nDo you want to start the program with this error (y/*): ";
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            system("cls");
            Menu();
        }
    }

    std::cout << "\nThe program exited successfully!\n";

    return 0;
}
