#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "point_calc.hh"

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
    auto cardsVec = readFile("input.txt");
    PointCalculator pCalc = PointCalculator();
    pCalc.readCardVec(cardsVec);
    auto p1Res = pCalc.calcCardPoints();

    std::cout << "Part 1 result: " << p1Res << "\n";

    auto p2res = pCalc.calcTotalNumOfCards();
    std::cout << "Part 2 result: " << p2res << "\n";

    return EXIT_SUCCESS;
}
