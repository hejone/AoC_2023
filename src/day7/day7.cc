/** Solution for day 7
* NOTE: Has solution only for part 2.
* To get solution for part 1, comment HandKindSolver::solve_hand
* call for handle_jokers and change 'J' back to value 11 in Poker::Symbol2Value
*/
#include <iostream>

#include "hands_handler.hh"
#include "util.hh"

int main() {
    auto read_file = util::readFile("input.txt");
    auto hands_handler = HandsHandler();
    hands_handler.parse_file(read_file);
    auto result2 = hands_handler.calculate_total_winnings();

    std::cout << "Part 2 result: " << result2 << "\n";
    return EXIT_SUCCESS;
}
