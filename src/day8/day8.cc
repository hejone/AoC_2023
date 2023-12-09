#include <iostream>

#include "util.hh"
#include "map_reader.hh"


int main() {
    auto read_file = util::readFile("input.txt");
    auto map_reader = MapReader();
    map_reader.read_map(read_file);
    auto result1 = map_reader.find_route();

    std::cout << "Part 1 result: " << result1 << "\n";

    return EXIT_SUCCESS;
}
