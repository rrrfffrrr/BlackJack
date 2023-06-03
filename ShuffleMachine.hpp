#pragma once
#include <vector>
#include <random>
#include "Card.hpp"

class ShuffleMachine {
    private:
        std::default_random_engine m_Shuffler;

    public:
        ShuffleMachine();
        ShuffleMachine(const ShuffleMachine&&) = delete;

    public:
        void Shuffle(std::vector<Card>& cards);
};