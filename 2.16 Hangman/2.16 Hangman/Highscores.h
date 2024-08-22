#pragma once
#include "GameLogic.h"
#include "HighscoreEntry.h"

class Highscores {
public:
    Highscores(Difficulty d);

    auto ReadListFromFile() -> bool;

    auto WriteListToFile() -> bool;

    auto PrintHighscores() -> void;

    auto AddHighscoreEntry(std::string player, std::string word, int attempts) -> bool;

    auto SortHighscores() -> void;

    auto ResetHighscores() -> bool;

private:
    HighscoreEntry m_list[100];
    std::string m_fileName;
    int m_numberOfEntries = 0;
};

