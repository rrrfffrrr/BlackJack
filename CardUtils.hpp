#pragma once
#include <vector>
#include "Card.hpp"

class CardUtils {
    public:
        static int CalculateMaximumScoreUnderOrEqualTargetScore(std::vector<Card>& cards, int targetScore = 21);
};