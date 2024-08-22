#include <algorithm>
#include "DrawingTool.h"


DrawingTool::DrawingTool(GameLogic &gamelogic)
    : m_gameLogic(gamelogic)
{
    switch (m_gameLogic.GetDifficulty()) {
        case Difficulty::Easy:
            // todo: determine letters shown at start
            break;
        case Difficulty::Medium:
            break;
        case Difficulty::Hard:
            break;
        default:
            break;
    }

    m_amountOfHidden = m_gameLogic.GetWord().length();
}

auto DrawingTool::DrawHangman() -> void
{
    std::cout << "\n====== HANGMAN ======" << std::endl;
    switch (m_gameLogic.GetAttempts()) {
        case 5:
            std::cout << std::setw(10) << std::setfill(' ')
                << "\n \n \n \n|" << std::endl;
            break;
        case 4:
            std::cout << std::setw(10) << std::setfill(' ')
                << "\n \n \n|\n|" << std::endl;
            break;
        case 3:
            std::cout << std::setw(10) << std::setfill(' ')
                << "\n|\n|\n|\n|" << std::endl;
            break;
        case 2:
            std::cout << std::setw(10) << std::setfill(' ')
                << "____\n|\n|\n|\n|" << std::endl;
            break;
        case 1:
            std::cout << std::setw(10) << std::setfill(' ')
                << "_________\n|\t|\n|\n|\n|" << std::endl;
            break;
        case 0:
            std::cout << std::setw(10) << std::setfill(' ')
                << "_________\n|\t|\n|\to\n|\t^\n|\t^" << std::endl;
            break;
    }
}

auto DrawingTool::PrintWord() -> void
{
    std::cout << "\n==== HIDDEN WORD ====" << std::endl;

    for (int i = 0; i < m_gameLogic.GetWord().length(); ++i) {
        char currentChar = m_gameLogic.GetWord()[i];
        bool printUnderscore = true;

        for (int j = 0; j < sizeof(m_foundLetters) / sizeof(m_foundLetters[0]); ++j) {
            if (currentChar == m_foundLetters[j]) {
                std::cout << m_foundLetters[j];
                printUnderscore = false;
            }
        }

        if (printUnderscore) {
            std::cout << "_";
        }
    }
    std::cout << std::endl;
}

auto DrawingTool::PrintHint() -> void
{
    std::cout << "\n======== TIP ========" << std::endl
        << m_gameLogic.GetHint() << std::endl;
}

auto DrawingTool::PrintRemainingAttempts() -> void
{
    std::cout << "Guesses left:\t" << m_gameLogic.GetAttempts() << std::endl;
}

auto DrawingTool::PrintWrongLetters() -> void
{
    if (m_amountOfWrong > 0) {
        std::cout << "Guessed wrong:\t";
        for (int i = 0; i < m_amountOfWrong; i++) {
            std::cout << m_wrongLetters[i] << ", ";
        }
        std::cout << std::endl;
    }
}

auto DrawingTool::MakeGuess(std::string guess) -> bool
{
    // only allow single character input
    if (guess.length() > 1) {
        return false;
    }


    // check if letter got guessed wrongly before
    for (int i = 0; i < m_amountOfWrong; i++) {
        if (m_wrongLetters[i] == guess[0]) {
            // wrong, but already guessed, so don't decrease attempts
            return false;
        }
    }

    // check if letter got guessed correctly before
    for (int i = 0; i < m_amountOfFound; i++) {
        if (m_foundLetters[i] == guess[0]) {
            // correct, but already guessed, so don't assign it again
            return true;
        }
    }

    if (Validator::ValidateGuess(guess, m_gameLogic.GetWord(), m_amountOfFound, m_amountOfHidden)) {
        m_foundLetters[m_amountOfFound] = guess[0];
        return true;
    } else {
        m_gameLogic.DecreaseAttempts();
        m_wrongLetters[m_amountOfWrong] = guess[0];
        ++m_amountOfWrong;
        return false;
    }
}
