#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "almanac.hh"

std::vector<std::string> readFile(const std::string& filePath) {
    std::ifstream input(filePath);
    if (!input.is_open()) {
        return std::vector<std::string>();
    }
    std::string line;
    auto outputVec = std::vector<std::string>();
    while(std::getline(input, line)) {
        outputVec.push_back(line);
    }
    return outputVec;
}


int main() {
    auto lines = readFile("input.txt");

    auto almanac = Almanac();
    almanac.read_input(lines);
    auto result1 = almanac.find_smallest_location_indv_seeds();

    std::cout << "Part 1 solution: " << result1 << "\n";

    auto result2 = almanac.find_smallest_location_ranges();

    std::cout << "Part 2 solution: " << result2 << "\n";

    return EXIT_SUCCESS;
}
