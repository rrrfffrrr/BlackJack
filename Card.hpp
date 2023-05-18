#pragma once
#include <string>

class Card {
    private:
        std::string m_Suit;
        std::string m_Rank;
        
    public:
        Card(const std::string suit, const std::string rank);

    public:
        inline std::string GetSuit() {
            return m_Suit;
        }
        inline std::string GetRank() {
            return m_Rank;
        }
        int GetScore();
        bool HasAltScore();
        int GetAltScore();
};