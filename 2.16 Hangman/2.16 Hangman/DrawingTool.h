#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "GameLogic.h"
#include "Validator.h"

class GameLogic;

class DrawingTool {
public:
    DrawingTool(GameLogic &gamelogic);

    auto DrawHangman() -> void;
    auto PrintWord() -> void;
    auto PrintHint() -> void;
    auto PrintRemainingAttempts() -> void;
    auto PrintWrongLetters() -> void;
    auto MakeGuess(std::string guess) -> bool;
    auto getAmountOfHidden() -> int
    {
        return m_amountOfHidden;
    }

private:
    GameLogic &m_gameLogic;

    char m_foundLetters[26];
    int m_amountOfFound = 0;

    char m_wrongLetters[26];
    int m_amountOfWrong = 0;

    int m_amountOfHidden = 0;
};