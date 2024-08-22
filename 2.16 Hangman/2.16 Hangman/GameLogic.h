#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "DrawingTool.h"
#include "WordBank.h"
#include "WordModifier.h"
#include "Highscores.h"
#include "Difficulty.h"

class DrawingTool;

class GameLogic {
public:
    auto StartGame() -> void;
    auto StartModifier() -> void;
    auto ViewAllHighscores() -> void;
    auto StartClearHighscore() -> void;
    auto DecreaseAttempts() -> bool
    {
        --m_attemptsLeft;
        if (m_attemptsLeft < 0) {
            return false;
        } else {
            return true;
        }
    }

    auto GetDifficulty() -> Difficulty
    {
        return m_difficulty;
    }
    auto GetWord() -> std::string
    {
        return m_word;
    }
    auto GetHint() -> std::string
    {
        return m_hint;
    }
    auto GetAttempts() -> int
    {
        return m_attemptsLeft;
    }

private:
    int m_attemptsLeft;
    Difficulty m_difficulty;
    std::string m_word;
    std::string m_hint;
    auto StartRound() -> void;
    auto NewHighscore() -> void;
};

