#pragma once
#include <string>

class HighscoreEntry {
public:
    HighscoreEntry(std::string p = "", std::string w = "", int a = 0);

    std::string getPlayer() const
    {
        return player;
    }
    void setPlayer(const std::string& newPlayer)
    {
        player = newPlayer;
    }

    std::string getWord() const
    {
        return word;
    }
    void setWord(const std::string& newWord)
    {
        word = newWord;
    }

    int getAttempts() const
    {
        return attempts;
    }
    void setAttempts(int newAttempts)
    {
        attempts = newAttempts;
    }

private:
    std::string player;
    std::string word;
    int attempts;
};
