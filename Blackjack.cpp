#include <iostream>
#include "Blackjack.hpp"
#include "CardUtils.hpp"

using namespace std;

const int kBlackjackScore = 21;
const int kDealerStopScore = 17;
const int kStartingCoins = 2000;
const int kAceAdditionalScore = 10;

const int kRank2Score[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };

enum class EGameResult {
    None,
    PlayerWin,
    DealerWin,
    Draw
};
enum class EGameEndReason {
    None,
    Score,
    Burst
};
enum class EGameState {
    Initialize,
    PreRound,
    Player,
    Dealer,
    PostRound,
    End
};

void Blackjack::Information() {
    cout
    << "A blackjack game\n"
    << "\n\n"
    << "21 card game that competes against the dealer.\n"
    << endl;
}

bool Blackjack::DrawCardInternal(Card& out) {
    if (m_Deck.empty()) {
        SetupNewDeckInternal();
    }

    out = m_Deck.back();
    m_Deck.pop_back();
    return true;
}

void Blackjack::DrawPlayer() {
    Card card;
    if (DrawCardInternal(card)) {
        m_PlayerHand.push_back(card);
    }
}
void Blackjack::DrawDealer() {
    Card card;
    if (DrawCardInternal(card)) {
        m_DealerHand.push_back(card);
    }
}

void Blackjack::ShowCurrentBoard(bool hide) {
    cout << "Dealer's hand: ";
    {
        int i = 0;
        if (hide) {
            for(; i < 1; ++i) {
                cout << "??" << " ";
            }
        }
        for(; i < m_DealerHand.size(); ++i) {
            auto card = m_DealerHand[i];
            cout << CardUtils::GetSuitCharacter(card.GetSuit()) << CardUtils::GetRankCharacter(card.GetRank()) << " ";
        }
    }
    cout << endl;
    
    cout << "Player's hand: ";
    for(int i = 0; i < m_PlayerHand.size(); ++i) {
        auto card = m_PlayerHand[i];
        cout << CardUtils::GetSuitCharacter(card.GetSuit()) << CardUtils::GetRankCharacter(card.GetRank()) << " ";
    }
    cout << endl;
}

bool Blackjack::IsBurst(std::vector<Card>& cards) {
    int score = CalculateScore(cards);
    return score > kBlackjackScore;
}
int Blackjack::CalculateScore(std::vector<Card>& cards) {
    int score = 0;
    int aces = 0;
    for(auto card : cards) {
        auto rank = card.GetRank();
        if (rank == ERank::Ace) {
            aces++;
        }
        score += kRank2Score[static_cast<int>(rank)];
    }
    for(auto i = 0; i < aces; ++i) {
        if (score + kAceAdditionalScore > kBlackjackScore)
            break;
        score += kAceAdditionalScore;
    }
    return score;
}

void Blackjack::SetupNewDeckInternal() {
    CardUtils::PushASetIntoDeck(m_Deck);
    m_ShuffleMachine.Shuffle(m_Deck);

    { // Discard first 2 card to prevent card counting
        Card temp;
        DrawCardInternal(temp);
        DrawCardInternal(temp);
    }
}

void Blackjack::Run() {
    EGameState gameState = EGameState::Initialize;
    cout << "Stating blackjack" << endl;

    m_DealerCoin = kStartingCoins;
    m_PlayerCoin = kStartingCoins;

    SetupNewDeckInternal();

    int currentBet = 0;
    char inputDrawCard = false;

    gameState = EGameState::PreRound;

    EGameResult gameResult = EGameResult::None;
    EGameEndReason gameEndReason = EGameEndReason::None;

    while(m_DealerCoin > 0 && m_PlayerCoin > 0) {
        switch (gameState)
        {
        case EGameState::PreRound: { // Starting a round
            cout << "Player coin: " << m_PlayerCoin << endl;
            cout << "Dealer coin: " << m_DealerCoin << endl;

            // Default bet
            m_PlayerCoin -= 100;
            m_DealerCoin -= 100;
            currentBet += 200;

            // Initial cards
            DrawDealer();
            DrawDealer();

            DrawPlayer();
            DrawPlayer();

            gameState = EGameState::Player;
            cout << endl;
        }
        break;
        case EGameState::Player: { // Player turn
            ShowCurrentBoard(true);
            if (CalculateScore(m_PlayerHand) == kBlackjackScore) {
                cout << "Player has 21 scores, end turn automatically." << endl;
                // It is max score, just end turn
                gameState = EGameState::Dealer;
                break;
            }
            cout << "Draw a card? (Y/N)" << endl ;
            cin >> inputDrawCard;

            switch (inputDrawCard)
            {
            case 'y':
            case 'Y': {
                DrawPlayer();
                if (IsBurst(m_PlayerHand)) {
                    ShowCurrentBoard(true);
                    gameResult = EGameResult::DealerWin;
                    gameEndReason = EGameEndReason::Burst;

                    gameState = EGameState::PostRound;
                }
            }
            break;
            case 'n':
            case 'N': {
                gameState = EGameState::Dealer;
            }
            break;
            default: break;
            }
        }
        break;
        case EGameState::Dealer: { // Dealer turn
            while(CalculateScore(m_DealerHand) < kDealerStopScore) {
                DrawDealer();
            }
            ShowCurrentBoard(false);

            if (CalculateScore(m_DealerHand) > kBlackjackScore) {
                gameResult = EGameResult::PlayerWin;
                gameEndReason = EGameEndReason::Burst;
            }

            gameState = EGameState::PostRound;
        }
        break;
        case EGameState::PostRound: { // End of round
            // Perform comparison and make result
            if (gameResult == EGameResult::None) {
                auto playerScore = CalculateScore(m_PlayerHand);
                auto dealerScore = CalculateScore(m_DealerHand);

                cout << "Player score: " << playerScore << endl;
                cout << "Dealer score: " << dealerScore << endl;

                if (playerScore == dealerScore) {
                    gameResult = EGameResult::Draw;
                    gameEndReason = EGameEndReason::Score;
                } else {
                    gameResult = (playerScore > dealerScore) ? EGameResult::PlayerWin : EGameResult::DealerWin;
                    gameEndReason = EGameEndReason::Score;
                }
            }

            // Show result
            m_PlayerHand.clear();
            m_DealerHand.clear();

            switch (gameResult)
            {
            case EGameResult::PlayerWin:
                if (gameEndReason == EGameEndReason::Burst) {
                    cout << "Dealer bursted, ";
                }
                cout << "Player win!" << endl;
                m_PlayerCoin += currentBet;
                currentBet = 0;
            break;
            case EGameResult::DealerWin:
                if (gameEndReason == EGameEndReason::Burst) {
                    cout << "Player bursted, ";
                }
                cout << "Dealer win!" << endl;
                m_DealerCoin += currentBet;
                currentBet = 0;
            break;
            case EGameResult::Draw: {
                cout << "Draw!" << endl;
                m_PlayerCoin += currentBet / 2;
                m_DealerCoin += currentBet / 2;
                currentBet = 0;
            }
            break;
            default: break;
            }

            gameState = EGameState::PreRound;
            gameResult = EGameResult::None;
            gameEndReason = EGameEndReason::None;
            cout << endl;
        }
        break;
        default: break;
        }
    }

    gameState = EGameState::End;

    cout << "=== Game result ===" << endl
        << "Player coin: " << m_PlayerCoin << endl
        << "Dealer coin: " << m_DealerCoin << endl;
}