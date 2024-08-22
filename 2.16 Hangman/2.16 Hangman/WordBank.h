#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "GameLogic.h"
#include "Difficulty.h"

class WordBank {
public:
    WordBank(Difficulty d);
    auto ReadWordsFromFile() -> bool;
    auto WriteWordsToFile() -> bool;
    auto GetRandomIndex() -> int;

    auto GetWord(int index) -> std::string
    {
        if (index > -1 && index < 50) {
            return m_words[index];
        } else {
            return "";
        }
    }
    auto GetHint(int index) -> std::string
    {
        if (index > -1 && index < 50) {
            return m_hints[index];
        } else {
            return "";
        }
    }

    friend class WordModifier;
private:
    int m_numberOfEntries = 0;
    std::string m_words[50];
    std::string m_hints[50];
    std::string m_fileName;
};