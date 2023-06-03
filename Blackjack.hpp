#pragma once
#include <vector>
#include "IGame.hpp"
#include "ShuffleMachine.hpp"

class Blackjack : public IGame {
    private:
        ShuffleMachine m_ShuffleMachine;

        std::vector<Card> m_Deck;

        std::vector<Card> m_DealerHand;
        std::vector<Card> m_PlayerHand;

        int m_DealerCoin;
        int m_PlayerCoin;

    public:
        Blackjack() = default;
        Blackjack(const Blackjack&&) = delete;
    
    private:
        void SetupNewDeckInternal();
        bool DrawCardInternal(Card& out);
        void DrawPlayer();
        void DrawDealer();
        /// @brief Show current board status
        /// @param hide Hide first dealer card
        void ShowCurrentBoard(bool hide);
        
        bool IsBurst(std::vector<Card>& cards);
        int CalculateScore(std::vector<Card>& cards);

    public:
        virtual void Information() override;
        virtual void Run() override;
};