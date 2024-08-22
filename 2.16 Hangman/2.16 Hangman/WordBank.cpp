#include <random>
#include <vector>
#include "WordBank.h"
#include "Difficulty.h"

WordBank::WordBank(Difficulty d)
{
    switch (d) {
        case Difficulty::Easy:
            m_fileName = "./Words/Easy.txt";
            break;
        case Difficulty::Medium:
            m_fileName = "./Words/Medium.txt";
            break;
        case Difficulty::Hard:
            m_fileName = "./Words/Hard.txt";
            break;
    }
}

auto WordBank::ReadWordsFromFile() -> bool
{
    std::ifstream wordsFile(m_fileName);

    if (!wordsFile || wordsFile.fail()) {
        return false;
    }

    int i = 0;
    std::string currentLine;
    while (std::getline(wordsFile, currentLine)) {
        // split function (modified from stackoverflow)
        std::vector<std::string> items;
        int pos = 0;
        std::string item;

        while ((pos = currentLine.find("-")) != std::string::npos) {
            item = currentLine.substr(0, pos);
            items.push_back(item);
            currentLine.erase(0, pos + 1);
        }
        items.push_back(currentLine);

        // set list items
        m_words[i] = items[0];
        if (items.size() < 2) { // check if there is a hint
            m_hints[i] = "No hint provided :(";
        } else {
            m_hints[i] = items[1];
        }
        ++i;
    }
    wordsFile.close();
    m_numberOfEntries = i; // ignore last increment
    return true;
}

auto WordBank::WriteWordsToFile() -> bool
{
    std::ofstream wordsFile(m_fileName, std::ios::out);

    if (!wordsFile || wordsFile.fail()) {
        return false;
    }

    for (int i = 0; i < m_numberOfEntries; ++i) {
        if (i > 0) {
            wordsFile << "\n";  // new lines between words, except before the first word
        }
        wordsFile << m_words[i] << "-" << m_hints[i]; // write the words with hints on a line, the hyphen is for reading them more easily
    }
    wordsFile.close();
    return true;
}


auto WordBank::GetRandomIndex() -> int
{
    // generate random number
    std::random_device r;
    std::mt19937 rng(r());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, m_numberOfEntries - 1);

    return dist6(rng);
}

