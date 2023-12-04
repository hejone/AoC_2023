#ifndef POINT_CALC_CC
#define POINT_CALC_CC

#include "card.hh"
#include <map>
#include <vector>
#include <string>

struct CardCount
{
    Card card;
    int count;

    CardCount(const Card& cd, int cnt) {
        card = cd;
        count = cnt;
    }
};


class PointCalculator {
public:
    PointCalculator() = default;
    ~PointCalculator() = default;

    void readCardVec(const std::vector<std::string>& cardVec);
    int calcCardPoints();
    int calcTotalNumOfCards();

private:
    std::map<int, CardCount> _cards;
};

#endif // POINT_CALC_CC
