#pragma once
#include <string>
#include "Difficulty.h"
#include "WordBank.h"

class WordBank;

class WordModifier {
public:
    WordModifier(Difficulty d, WordBank &wb);

    auto PrintWords() -> void;
    auto AddWord(std::string newWord, std::string newHint) -> bool;
    auto DeleteEntry(int index) -> bool;
    auto ReplaceWord(int index, std::string newWord, std::string newHint) -> bool;
private:
    WordBank &m_wordbank;
    Difficulty m_difficulty;
    auto AddWord(int index, std::string newWord, std::string newHint) -> bool;

};
