#ifndef POKER_HAND_HH
#define POKER_HAND_HH

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>

namespace Poker {
const std::map<char, int> Symbol2Value {
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'J', 0},
    {'Q', 12},
    {'K', 13},
    {'A', 14}
};

enum class HandKind {
    HIGH_CARD = 0,
    PAIR = 1,
    TWO_PAIRS = 2,
    THREE_OF_KIND = 3,
    FULL_HOUSE = 4,
    FOUR_OF_KIND = 5,
    FIVE_OF_KIND = 6
};

struct HandKindSolver {
    HandKindSolver() = delete;

    struct NumberOfMatches {
        int five = 0;
        int four = 0;
        int three = 0;
        int two = 0;
        int one = 0;
    };

    static HandKind solve_hand(const std::string& hand_to_solve);
};

class PokerHand {
public:
    PokerHand() = default;
    PokerHand(std::string hand, int bid, HandKind hand_kind);
    ~PokerHand() = default;

    bool operator<(const PokerHand& other);

    inline HandKind get_hand_kind() const {
        return _hand_kind;
    }

    inline std::string get_orig_hand() const {
        return _original_hand;
    }

    inline int get_bid() const {
        return _bid;
    }

    static PokerHand read_row(const std::string& row);

private:
    std::string _original_hand;
    HandKind _hand_kind;
    int _bid;
};

} // Poker
#endif // POKER_HAND_HH
