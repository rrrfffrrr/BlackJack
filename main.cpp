#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "Card.hpp"
#include "ShuffleMachine.hpp"

using namespace std;

int DiscardAmountToPreventCounting = 2;

int TargetScore = 21;
int DealerFreezeScore = 17;

const int Scores[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};


int main() {
    ShuffleMachine machine;
    machine.Initialize();
    machine.PreventCardCounting(DiscardAmountToPreventCounting);
    
    vector<Card> dealerHand;
    vector<Card> playerHand;

    return 0;
}