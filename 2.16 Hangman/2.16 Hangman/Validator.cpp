#include "Validator.h"

bool Validator::ValidateGuess(const std::string & guess, const std::string & hiddenWord, int & amountOfFound, int & amountOfHidden)
{
    if (guess.length() == 1 && std::isalpha(guess[0]) && hiddenWord.find(guess) != std::string::npos) {
        // count how many times the same letter appears
        std::string::difference_type sameLetter = std::count(hiddenWord.begin(), hiddenWord.end(), guess[0]);

        amountOfFound++;
        amountOfHidden -= sameLetter;
        return true;
    }
    return false;
}

bool Validator::ValidateHint(const std::string word, const std::string hint)
{
    // check if hint contains word
    if (hint.find(word) != std::string::npos) {
        return false;
    }
    return true;
}

bool Validator::CheckWin(const int hiddenCount)
{
    return hiddenCount == 0;
}
