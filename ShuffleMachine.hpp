#pragma once
#include <vector>
#include <random>
#include "Card.hpp"

class ShuffleMachine {
    private:
        std::vector<Card> m_Cards;
        std::default_random_engine m_Shuffler;

    public:
        ShuffleMachine();

    private:
        void AddCards();
        void Shuffle();
    public:
        void Initialize();
        void PreventCardCounting(int amount);
        Card Draw();
};