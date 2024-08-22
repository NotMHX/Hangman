#include <algorithm>
#include <cctype>
#include <stdlib.h>
#include "GameLogic.h"

const int EasyAttempts = 5;
const int MediumAttempts = 4;
const int HardAttempts = 3;

auto GameLogic::StartGame() -> void
{
    std::cout << "\nSelect your difficulty:\n1. Easy\n2. Medium\n3. Hard"
        << std::endl;
    bool falseInput = true;
    while (falseInput) {
        int selectedDiff;
        std::cin >> selectedDiff;
        switch (selectedDiff) {
            case 1:
                m_difficulty = Difficulty::Easy;
                m_attemptsLeft = EasyAttempts;
                falseInput = false;
                break;
            case 2:
                m_difficulty = Difficulty::Medium;
                m_attemptsLeft = MediumAttempts;
                falseInput = false;
                break;
            case 3:
                m_difficulty = Difficulty::Hard;
                m_attemptsLeft = HardAttempts;
                falseInput = false;
                break;
            default:
                std::cout << "\nInvalid input. Try again:" << std::endl;
        }
    }

    WordBank wb(m_difficulty);
    wb.ReadWordsFromFile();
    int rng = wb.GetRandomIndex();
    m_word = wb.GetWord(rng);
    m_hint = wb.GetHint(rng);

    system("cls");
    this->StartRound();
    system("pause");
}


auto GameLogic::StartRound() -> void
{
    DrawingTool dt(*this);
    bool lastGuessCorrect = false;
    bool isFirstAttempt = true;

    while (m_attemptsLeft > 0) {
        if (!isFirstAttempt) {
            std::cout << "\n=============" << std::endl;
            if (lastGuessCorrect) {
                std::cout << "|| \x1B[92mCORRECT\033[0m ||" << std::endl;
            } else {
                std::cout << "||  \x1B[91mWRONG\033[0m  ||" << std::endl;
            }
            std::cout << "=============" << std::endl;
        }

        dt.DrawHangman();
        dt.PrintWord();
        if (m_attemptsLeft == 1) {
            dt.PrintHint();
        }
        std::cout << "\n---------------------" << std::endl;
        dt.PrintWrongLetters();
        dt.PrintRemainingAttempts();
        std::cout << "---------------------\n" << std::endl;
        std::cout << "Enter a letter: ";
        std::string guess;
        std::cin >> guess;

        // convert to lowercase
        std::transform(guess.begin(), guess.end(), guess.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (dt.MakeGuess(guess)) {
            lastGuessCorrect = true;
        } else {
            lastGuessCorrect = false;
        }

        if (Validator::CheckWin(dt.getAmountOfHidden())) {
            std::cout << "Congrats :D\nYou found the word " << m_word << "!!" << std::endl;
            this->NewHighscore();
            return;
        }
        isFirstAttempt = false;
        system("cls");
    }
    dt.DrawHangman();
    std::cout << "You didn't find it :c\nThe word was: " << m_word << std::endl;
}

auto GameLogic::NewHighscore() -> void
{
    Highscores hs(m_difficulty);
    hs.ReadListFromFile();

    // get total attempts
    int totalAttempts = 0;
    switch (m_difficulty) {
        case Difficulty::Easy:
            totalAttempts = EasyAttempts;
            break;
        case Difficulty::Medium:
            totalAttempts = MediumAttempts;
            break;
        case Difficulty::Hard:
            totalAttempts = HardAttempts;
            break;
    }

    std::cout << "Enter your name to add to the highscore list: ";
    std::string player;
    std::cin >> player;

    hs.AddHighscoreEntry(player, m_word, (totalAttempts - m_attemptsLeft + 1));
    hs.SortHighscores();

    system("cls");
    hs.PrintHighscores();
    hs.WriteListToFile();
}

auto GameLogic::ViewAllHighscores() -> void
{
    std::cout << "\n\n=== Highscores: Easy ===" << std::endl;
    Highscores *hs1 = new Highscores(Difficulty::Easy);
    if (hs1->ReadListFromFile()) {
        hs1->PrintHighscores();
    } else {
        std::cout << "Error with reading the easy highscore file." << std::endl;
    }
    delete hs1;

    std::cout << "\n\n== Highscores: Medium ==" << std::endl;
    Highscores *hs2 = new Highscores(Difficulty::Medium);
    if (hs2->ReadListFromFile()) {
        hs2->PrintHighscores();
    } else {
        std::cout << "Error with reading the medium highscore file." << std::endl;
    }
    delete hs2;

    std::cout << "\n\n=== Highscores: Hard ===" << std::endl;
    Highscores *hs3 = new Highscores(Difficulty::Hard);
    if (hs3->ReadListFromFile()) {
        hs3->PrintHighscores();
    } else {
        std::cout << "Error with reading the hard highscore file." << std::endl;
    }
    delete hs3;

    std::cout << "\n\nYou can add your high score when you win!" << std::endl;
    system("pause");
}

auto GameLogic::StartClearHighscore() -> void
{
    std::cout << "Are you sure you want to clear *all* highscores? This cannot be undone. [y/n]" << std::endl;
    char choice;
    std::cin >> choice;
    if (choice != 'y') {
        return;
    }
    bool success = false;

    Highscores *hs1 = new Highscores(Difficulty::Easy);
    success = hs1->ResetHighscores();
    delete hs1;

    Highscores *hs2 = new Highscores(Difficulty::Medium);
    success = hs2->ResetHighscores();
    delete hs2;

    Highscores *hs3 = new Highscores(Difficulty::Hard);
    success = hs3->ResetHighscores();
    delete hs3;

    if (success) {
        std::cout << "Successfully cleared all highscores." << std::endl;
    } else {
        std::cout << "Error with resetting highscores." << std::endl;
    }
    system("pause");
}


auto GameLogic::StartModifier() -> void
{
    std::cout << "\nWhich word list would you like to view?\n1. Easy\n2. Medium\n3. Hard"
        << std::endl;

    bool falseInput = true;
    while (falseInput) {
        int selectedDiff;
        std::cin >> selectedDiff;
        switch (selectedDiff) {
            case 1:
                m_difficulty = Difficulty::Easy;
                falseInput = false;
                break;
            case 2:
                m_difficulty = Difficulty::Medium;
                falseInput = false;
                break;
            case 3:
                m_difficulty = Difficulty::Hard;
                falseInput = false;
                break;
            default:
                std::cout << "\nInvalid input. Try again:" << std::endl;
        }
    }
    system("cls");
    WordBank wb(m_difficulty);
    WordModifier wm(m_difficulty, wb);
    wb.ReadWordsFromFile();
    wm.PrintWords();
    std::cout << "\n==== Options ====" << std::endl
        << "1. Add new word\n2. Edit word\n3. Edit hint\n4. Delete entry\n5. Go back" << std::endl;
    int selectedOption;
    std::cin >> selectedOption;

    std::string newWord;
    std::string newHint;
    int selectedEntry;
    if (selectedOption >= 2 && selectedOption <= 4) {
        std::cout << "\nWhich entry would you like to modify?" << std::endl;
        std::cin >> selectedEntry;
    }

    switch (selectedOption) {
        case 1:
            std::cout << "\nEnter a new word: ";
            std::cin >> newWord;
            std::cout << "\nEnter a hint for that word: ";
            std::cin.ignore();
            getline(std::cin, newHint);
            if (wm.AddWord(newWord, newHint) && wb.WriteWordsToFile()) {
                std::cout << "Successfully added word " << newWord << "." << std::endl;
                break;
            } else {
                std::cout << "Error with adding word " << newWord << ".";
                break;
            }
        case 2:
            std::cout << "\nEnter a new word for entry " << selectedEntry << ": ";
            std::cin >> newWord;
            // only edit word, keep hint the same
            if (wm.ReplaceWord(selectedEntry - 1, newWord, wb.GetHint(selectedEntry - 1)) && wb.WriteWordsToFile()) {
                std::cout << "Successfully edited word " << selectedEntry << "." << std::endl;
                break;
            } else {
                std::cout << "Error with editing word " << selectedEntry << "." << std::endl;
                break;
            }
        case 3:
            std::cout << "\nEnter a new hint for entry " << selectedEntry << ": ";
            std::cin.ignore();
            getline(std::cin, newHint);
            // only edit hint, keep word the same
            if (wm.ReplaceWord(selectedEntry - 1, wb.GetWord(selectedEntry - 1), newHint) && wb.WriteWordsToFile()) {
                std::cout << "Successfully edited hint " << selectedEntry << "." << std::endl;
                break;
            } else {
                std::cout << "Error with editing hint " << selectedEntry << "." << std::endl
                    << "Make sure your hint doesn't contain the hidden word!" << std::endl;
                break;
            }
        case 4:
            if (wm.DeleteEntry(selectedEntry - 1) && wb.WriteWordsToFile()) {
                std::cout << "Successfully deleted entry " << selectedEntry << "." << std::endl;
                break;
            } else {
                std::cout << "Error with deleting entry " << selectedEntry << "." << std::endl;
                break;
            }
        case 5:
            return;
    }
    system("pause");
}