#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "coord_handler.hh"

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
    auto mapStr = readFile("input.txt");
    auto coordHandler = CoordHandler(mapStr);
    int32_t part1Res = coordHandler.calcPartSum();
    std::cout << "Part 1 result: " << part1Res << "\n";

    int32_t part2Res = coordHandler.calcGearRatioSum();
    std::cout << "Part 2 result: " << part2Res << "\n";
    return EXIT_SUCCESS;
}
