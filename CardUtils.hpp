#pragma once
#include <vector>
#include <string>
#include "Card.hpp"

struct CardUtils {
    static std::string GetSuitCharacter(ESuit suit);
    static std::string GetRankCharacter(ERank rank);
    static void PushASetIntoDeck(std::vector<Card>& cards);
};