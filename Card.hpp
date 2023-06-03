#pragma once

enum class ESuit {
    Spade = 0,
    Heart,
    Club,
    Diamond,

    Count
};

enum class ERank {
    Ace = 0,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,

    Count
};

class Card {
    private:
        ESuit m_Suit;
        ERank m_Rank;
        
    public:
        Card();
        Card(const ESuit suit, const ERank rank);

    public:
        inline ESuit GetSuit() {
            return m_Suit;
        }
        inline ERank GetRank() {
            return m_Rank;
        }
};