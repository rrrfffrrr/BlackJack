#include "Card.hpp"

Card::Card() : Card(ESuit::Spade, ERank::Ace) {}
Card::Card(const ESuit suit, const ERank rank) : m_Suit(suit), m_Rank(rank) {}