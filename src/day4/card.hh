#ifndef CARD_HH
#define CARD_HH

#include <set>
#include <string>

inline static std::string _ALL_NUMS = "1234567890";

class Card {
public:
    Card() = default;
    Card(int cardNum, const std::set<int>& numbers, const std::set<int>& winNumbers);
    ~Card() = default;

    static Card readRow(const std::string& row);
    int calcPoints();
    int winNum();
    int inline cardNum() {
        return _cardNum;
    };

private:
    int _cardNum;
    std::set<int> _numbers = {};
    std::set<int> _winNumbers = {};
};

#endif // CARD_HH
