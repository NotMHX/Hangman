#include <vector>
#include <algorithm>
#include "Highscores.h"

Highscores::Highscores(Difficulty d)
{
    switch (d) {
        case Difficulty::Easy:
            m_fileName = "./Highscores/Easy.txt";
            break;
        case Difficulty::Medium:
            m_fileName = "./Highscores/Medium.txt";
            break;
        case Difficulty::Hard:
            m_fileName = "./Highscores/Hard.txt";
            break;
    }
}

auto Highscores::ReadListFromFile() -> bool
{
    std::ifstream listFile(m_fileName);

    if (!listFile || listFile.fail()) {
        return false;
    }

    int i = 0;
    std::string currentLine;
    while (std::getline(listFile, currentLine)) {

        // split function (modified from stackoverflow)
        std::vector<std::string> items;
        int pos = 0;
        std::string item;

        while ((pos = currentLine.find(",")) != std::string::npos) {
            item = currentLine.substr(0, pos);
            items.push_back(item);
            currentLine.erase(0, pos + 1);
        }
        items.push_back(currentLine);

        // set list items
        m_list[i].setPlayer(items[0]);
        m_list[i].setWord(items[1]);
        m_list[i].setAttempts(std::stoi(items[2]));
        ++i;
    }
    listFile.close();
    m_numberOfEntries = i; // ignore last increment
    return true;
}

auto Highscores::WriteListToFile() -> bool
{
    std::ofstream listFile(m_fileName, std::ios::out);

    if (!listFile || listFile.fail()) {
        return false;
    }

    for (int i = 0; i < m_numberOfEntries; ++i) {
        if (i > 0) {
            listFile << "\n";  // new lines between words, except before the first word
        }
        listFile << m_list[i].getPlayer() << "," << m_list[i].getWord() << "," << m_list[i].getAttempts();
    }

    listFile.close();
    return true;
}

auto Highscores::PrintHighscores() -> void
{
    std::cout << "Rank\tPlayer\t\tAtt.\tWord" << std::endl
        << "------------------------------------------" << std::endl;
    for (int i = 0; i < m_numberOfEntries; ++i) {
        std::cout << "#" << i + 1 << "\t" << m_list[i].getPlayer() << "\t\t" << m_list[i].getAttempts() << "\t\"" << m_list[i].getWord() << "\"" << std::endl;
    }
}

auto Highscores::AddHighscoreEntry(std::string player, std::string word, int attempts) -> bool
{
    // create new entry and add it to the array
    HighscoreEntry add(player, word, attempts);
    m_list[m_numberOfEntries] = add;

    // check if add worked
    if (m_list[m_numberOfEntries].getPlayer() != player) {
        return false;
    } else {
        ++m_numberOfEntries;
        return true;
    }
}

auto Highscores::SortHighscores() -> void
{
    // custom comparison function
    auto compareByAttempts = [](const HighscoreEntry& a, const HighscoreEntry& b) {
        return a.getAttempts() < b.getAttempts();
        };

    // sort array by lowest attempts
    std::sort(m_list, m_list + m_numberOfEntries, compareByAttempts);
}

auto Highscores::ResetHighscores() -> bool
{
    std::fill_n(m_list, m_numberOfEntries, HighscoreEntry());
    m_numberOfEntries = 0;
    return this->WriteListToFile();
}
