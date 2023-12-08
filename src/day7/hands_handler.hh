#ifndef HANDS_HANDLER_HH
#define HANDS_HANDLER_HH

#include <set>
#include <vector>
#include <string>
#include <memory>
#include <inttypes.h>

#include "poker_hand.hh"

using Poker::PokerHand;

class HandsHandler {

struct set_comparator {
    bool operator() (const std::unique_ptr<PokerHand>& f, const std::unique_ptr<PokerHand>& s) const {
        return *f < *s;
    }
};

public:
    HandsHandler() = default;

    void parse_file(const std::vector<std::string>& read_file);

    int64_t calculate_total_winnings();

private:
    std::set<std::unique_ptr<Poker::PokerHand>, set_comparator> _poker_hands = {};
};

#endif // HANDS_HANDLER_HH
