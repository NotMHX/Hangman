#pragma once
#include <string>

struct Validator {
    static bool ValidateGuess(const std::string& guess, const std::string& hiddenWord, int & amountOfFound, int & amountOfHidden);
    static bool ValidateHint(const std::string word, const std::string hint);
    static bool CheckWin(const int hiddenCount);
};

