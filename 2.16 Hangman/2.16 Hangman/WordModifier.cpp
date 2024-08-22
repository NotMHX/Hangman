#include "WordModifier.h"

WordModifier::WordModifier(Difficulty d, WordBank &wb)
    : m_wordbank(wb), m_difficulty(d)
{
}

auto WordModifier::PrintWords() -> void
{
    std::cout << std::left << std::setw(5) << "Nr." << std::setw(20) << " Word" << " Hint" << std::endl
        << "----------------------------------------------------" << std::endl;
    for (int i = 0; i < m_wordbank.m_numberOfEntries; ++i) {
        std::cout << "#" << std::left << std::setw(5) << i + 1 << std::setw(20) << m_wordbank.m_words[i] << m_wordbank.m_hints[i] << std::endl;
    }
}

auto WordModifier::AddWord(std::string newWord, std::string newHint) -> bool
{
    return AddWord(m_wordbank.m_numberOfEntries, newWord, newHint);
}

auto WordModifier::AddWord(int index, std::string newWord, std::string newHint) -> bool
{
    if (index < 0 || index > m_wordbank.m_numberOfEntries
        || !Validator::ValidateHint(newWord, newHint)) {
        return false;
    }

    // move words ahead by 1
    for (int i = m_wordbank.m_numberOfEntries - 1; i >= index + 1; --i) {
        m_wordbank.m_words[i + 1] = m_wordbank.m_words[i];
        m_wordbank.m_hints[i + 1] = m_wordbank.m_hints[i];
    }

    m_wordbank.m_words[index] = newWord;
    m_wordbank.m_hints[index] = newHint;
    ++m_wordbank.m_numberOfEntries;
    return m_wordbank.m_words[index] == newWord;
}

auto WordModifier::DeleteEntry(int index) -> bool
{
    if (index >= 0 && index < m_wordbank.m_numberOfEntries) {

        for (int i = index; i < m_wordbank.m_numberOfEntries - 1; ++i) {
            m_wordbank.m_words[i] = m_wordbank.m_words[i + 1];
            m_wordbank.m_hints[i] = m_wordbank.m_hints[i + 1];
        }
        --m_wordbank.m_numberOfEntries;
        return true;
    } else
        return false;
}

auto WordModifier::ReplaceWord(int index, std::string newWord, std::string newHint) -> bool
{
    if (DeleteEntry(index) && AddWord(index, newWord, newHint)) {
        return m_wordbank.m_words[index] == newWord;
    }
    return false;
}
