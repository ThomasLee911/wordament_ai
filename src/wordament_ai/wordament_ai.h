#ifndef WORDAMENT_AI_WORDAMENT_AI_H_
#define WORDAMENT_AI_WORDAMENT_AI_H_

#include <cstdint>
#include <string>
#include <vector>
#include <stack>
#include "wordament_ai/dictionary.h"


namespace wordament_ai
{

class WordamentAI
{
 public:
    enum { GAME_MAP_SIZE = 4 };
    explicit WordamentAI(const std::vector<std::string> &dictionary_files);
    ~WordamentAI() {}

    std::int_least32_t dictionary_word_count() const
    { return dictionary_word_count_; }
    int FindWords(const std::string game_map[][GAME_MAP_SIZE]);

 private:
    struct Node;

    static void PrintSolution(const Node *last_node);

    Dictionary dictionary_;
    std::int_least32_t dictionary_word_count_;
    std::stack<Node *> node_stack_;
};

}  // namesapce wordament_ai

#endif  // WORDAMENT_AI_WORDAMENT_AI_H_