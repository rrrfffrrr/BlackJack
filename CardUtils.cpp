#include "CardUtils.hpp"

using namespace std;

const string Suits[] = { "♠", "♡", "♣", "◇" };
const string Ranks[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

string CardUtils::GetSuitCharacter(ESuit suit) {
    return Suits[static_cast<int>(suit)];
}

string CardUtils::GetRankCharacter(ERank rank) {
    return Ranks[static_cast<int>(rank)];
}

void CardUtils::PushASetIntoDeck(std::vector<Card>& cards) {
    for(auto suit = 0; suit < static_cast<int>(ESuit::Count); ++suit) {
        for(auto rank = 0; rank < static_cast<int>(ERank::Count); ++rank) {
            cards.push_back(Card(static_cast<ESuit>(suit), static_cast<ERank>(rank)));
        }
    }
}