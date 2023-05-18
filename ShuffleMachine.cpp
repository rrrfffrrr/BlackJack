#include "ShuffleMachine.hpp"
#include "CardDefinitions.hpp"

using namespace std;

ShuffleMachine::ShuffleMachine() : m_Cards() {
    auto rd = random_device {};
    this->m_Shuffler = default_random_engine { rd() };
}

void ShuffleMachine::AddCards() {
    for(auto i = 0; i < 4; ++i) {
        for(auto j = 0; j < 13; ++j) {
            m_Cards.push_back(Card(Suits[i], Ranks[j]));
        }
    }
}
void ShuffleMachine::Shuffle() {
    shuffle(m_Cards.begin(), m_Cards.end(), m_Shuffler);
}

void ShuffleMachine::Initialize() {
    AddCards();
    Shuffle();
}
void ShuffleMachine::PreventCardCounting(int amount) {
    for(auto i = 0; i < amount && !m_Cards.empty(); ++i) {
        m_Cards.pop_back();
    }
}
Card ShuffleMachine::Draw() {
    if (m_Cards.empty()) {
        Initialize();
    }
    
    auto card = m_Cards.back();
    m_Cards.pop_back();
    return card;
}