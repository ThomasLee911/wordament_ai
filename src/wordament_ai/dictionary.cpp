#include "dictionary.h"
#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>

namespace wordament_ai
{

std::int_least32_t Dictionary::ReadWordsFromFile(const char *filename)
{
    std::ifstream fin(filename);
    if (!fin.is_open())  // cannot read the file
        return 0;        // nothing read

    std::int_least32_t word_count = 0;
    std::string word;
    while (fin >> word)
    {
        if (word.size() < LEAST_LENGTH)  // word is too short
            continue;
        // then word has at least LEAST_LENGTH character
        // transform it into lower case
        std::transform(word.begin(), word.end(), word.begin(), tolower);
        for (auto word_iter = word.begin() + 1; word_iter != word.end();
             ++word_iter)
        {
            // for every sub-word
            std::string sub_word(word.begin(), word_iter);
            auto insert_reslut = word_map_.insert(std::pair<std::string, int>
                                                  (sub_word, IS_SUB_WORD));
            // if the sub-word was not in the map, it is added correctly.
            // if the sub-word was already in the map, nothing happened,
            // so we make sure it has "IS_SUB_WORD" property
            if (insert_reslut.second == false)
                insert_reslut.first->second |= IS_SUB_WORD;
        }
        // for the word
        auto insert_reslut = word_map_.insert(std::pair<std::string, int>
                                              (word, IS_WORD));
        // if the word was not in the map, it is added correctly.
        // if the word was already in the map, nothing happened,
        // so we make sure it has "IS_WORD" property, add increase
        // counter when it is a new word
        if (insert_reslut.second == true)  // new word
        {
            word_count++;
        }
        else  // it is a sub-word or word existed in the dictionary
        {
            if ((insert_reslut.first->second & IS_WORD) == 0)  // new word
            {
                insert_reslut.first->second |= IS_WORD;
                word_count++;
            }
        }
    }

    return word_count;
}

int Dictionary::LookUp(const std::string &word) const
{
    auto iter = word_map_.find(word);
    if (iter == word_map_.end())  // not in map
        return 0;

    return iter->second;  // return the property
}

void Dictionary::Show() const
{
    for (auto entry : word_map_)
    {
        std::cout.width(10);
        std::cout << entry.first << ' ' << entry.second << std::endl;
    }
}

}  // namespace wordament_ai
