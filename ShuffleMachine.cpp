#include "ShuffleMachine.hpp"

using namespace std;

ShuffleMachine::ShuffleMachine() {
    auto rd = random_device {};
    this->m_Shuffler = default_random_engine { rd() };
}

void ShuffleMachine::Shuffle(std::vector<Card>& cards) {
    shuffle(cards.begin(), cards.end(), m_Shuffler);
}