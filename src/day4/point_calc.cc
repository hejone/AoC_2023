#include "point_calc.hh"

void PointCalculator::readCardVec(const std::vector<std::string>& cardVec) {
    for(const auto& row : cardVec) {
        Card newCard = Card::readRow(row);
        _cards.insert({newCard.cardNum(), {newCard, 1}});
    }
}

int PointCalculator::calcCardPoints()
{
    int sum = 0;
    for (auto& [_, cardPair]: _cards) {
        sum += cardPair.card.calcPoints();
    }
    return sum;
}

int PointCalculator::calcTotalNumOfCards()
{
    int cardSum = 0;
    for (size_t cardNum = 1; cardNum < _cards.size() + 1; ++cardNum) {
        auto currPair = _cards.at(cardNum);
        cardSum += currPair.count;
        auto winCount = currPair.card.winNum();
        if(winCount == 0) {
            continue;
        }
        for (size_t i = cardNum + 1; i < _cards.size() + 1 && i < cardNum + winCount + 1; ++i) {
            _cards.at(i).count += currPair.count;
        }
    }
    return cardSum;
}
