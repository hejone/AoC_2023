#include "poker_hand.hh"

namespace Poker {

    void handle_jokers(std::map<char, int>& amounts_by_symbol_ref) {
        if (amounts_by_symbol_ref.find('J') != amounts_by_symbol_ref.end()) {
            int num_of_jokers = amounts_by_symbol_ref.at('J');
            if (num_of_jokers == 5) {
                return;
            }
            amounts_by_symbol_ref.erase('J');
            auto it = amounts_by_symbol_ref.begin();
            std::pair<char, int> biggest = *it;
            ++it;
            for(; it != amounts_by_symbol_ref.end(); ++it) {
                if(it->second > biggest.second) {
                    biggest = *it;
                }
            }
            amounts_by_symbol_ref.at(biggest.first) += num_of_jokers;
        }
    }

    HandKind HandKindSolver::solve_hand(const std::string& hand_to_solve) {
        std::map<char, int> amounts_by_symbol = {};
        for (const char& symb : hand_to_solve) {
            if(amounts_by_symbol.find(symb) == amounts_by_symbol.end()) {
                amounts_by_symbol.insert({symb, 1});
            } else {
                amounts_by_symbol.at(symb) += 1;
            }
        }

        handle_jokers(amounts_by_symbol);

        NumberOfMatches nums = {};
        for (const auto& [_, amount] : amounts_by_symbol) {
            switch (amount) {
            case 5:
                nums.five += 1;
                break;
            case 4:
                nums.four += 1;
                break;
            case 3:
                nums.three += 1;
                break;
            case 2:
                nums.two += 1;
                break;
            default:
                nums.one += 1;
                break;
            }
        }

        HandKind handk = HandKind::HIGH_CARD;

        if (nums.five) {
            handk = HandKind::FIVE_OF_KIND;
        } else if(nums.four) {
            handk = HandKind::FOUR_OF_KIND;
        } else if(nums.three) {
            if (nums.two) {
                handk = HandKind::FULL_HOUSE;
            } else {
                handk = HandKind::THREE_OF_KIND;
            }
        } else if (nums.two == 2) {
            handk = HandKind::TWO_PAIRS;
        } else if (nums.two) {
            handk = HandKind::PAIR;
        }
        return handk;
    }

    PokerHand::PokerHand(std::string hand, int bid, HandKind hand_kind) :
        _original_hand(hand), _bid(bid), _hand_kind(hand_kind) {}

    bool PokerHand::operator<(const PokerHand& other) {
        if (_hand_kind < other.get_hand_kind()) {
            return true;
        } else if (_hand_kind > other.get_hand_kind()) {
            return false;
        }
        auto other_orig = other.get_orig_hand();
        int this_val, other_val;
        for (int i = 0; i < _original_hand.size(); ++i) {
            this_val = Symbol2Value.at(_original_hand.at(i));
            other_val = Symbol2Value.at(other_orig.at(i));
            if (this_val < other_val) {
                return true;
            } else if (this_val != other_val) {
                return false;
            }
        }
        return false;
    }

    PokerHand PokerHand::read_row(const std::string& row) {
        int split_point = row.find_first_of(' ');
        std::string orig_hand = row.substr(0, split_point);
        int bid = std::stoi(row.substr(split_point + 1).c_str());
        auto amounts_by_symbol = std::map<char, int>();
        for (const char& symb : orig_hand) {
            if(amounts_by_symbol.find(symb) == amounts_by_symbol.end()) {
                amounts_by_symbol.insert({symb, 1});
            } else {
                amounts_by_symbol.at(symb) += 1;
            }
        }

        HandKind handk = HandKindSolver::solve_hand(orig_hand);

        return PokerHand(orig_hand, bid, handk);
    }
}
