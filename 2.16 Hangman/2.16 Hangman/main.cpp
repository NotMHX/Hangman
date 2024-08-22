#include <iostream>
#include <stdlib.h>
#include "GameLogic.h"

int main()
{
    while (true) {
        // cyan text color
        std::cout << "\x1B[96m";
        std::cout << R"(   __ _____   _  _________  ______   _  __
  / // / _ | / |/ / ___/  |/  / _ | / |/ /
 / _  / __ |/    / (_ / /|_/ / __ |/    /
/_//_/_/ |_/_/|_/\___/_/  /_/_/ |_/_/|_/  )" << std::endl;
        std::cout << "\033[0m";

        std::cout << "\nWelcome to Hangman!\n1. Play Game\n2. Manage Word Lists\n3. View Highscores\n4. Clear Highscores\n5. Quit"
            << std::endl;
        int input;
        std::cin >> input;
        system("cls");

        GameLogic gl;
        switch (input) {
            case 1:
                gl.StartGame();
                break;
            case 2:
                gl.StartModifier();
                break;
            case 3:
                gl.ViewAllHighscores();
                break;
            case 4:
                gl.StartClearHighscore();
                break;
            case 5:
                std::cout << "Thanks for playing!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid option." << std::endl;
                break;
        }
        system("cls");
    }
}