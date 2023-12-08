#include "hands_handler.hh"

void HandsHandler::parse_file(const std::vector<std::string> &read_file) {
    for (const auto& row : read_file) {
        _poker_hands.insert(std::make_unique<PokerHand>(PokerHand::read_row(row)));
    }
}

int64_t HandsHandler::calculate_total_winnings() {
    int rank = 1;
    int64_t winnings = 0;
    for (const auto& hand : _poker_hands) {
        winnings += rank * hand->get_bid();
        rank++;
    }
    return winnings;
}
