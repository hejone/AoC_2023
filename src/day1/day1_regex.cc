/* Solution for AoC 2023 day 1
The regex solution
*/
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <stdexcept>


std::unordered_map<std::string, int> LETTER_NUMS {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

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

int getNum(const std::string& snum) {
    int num = -1;
    if(std::all_of(snum.begin(), snum.end(), isdigit)) {
        num = std::stoi(snum);
    } else {
        num = LETTER_NUMS[snum];
    }
    return num;
}

std::vector<std::pair<int, int>> findLinesfirstLastNumber(const std::vector<std::string>& lines,
                                                          std::regex pattern) {
    std::vector<std::pair<int, int>> result;
    result.reserve(lines.size());
    int linNum = 0;
    for (const auto& line : lines) {
        std::pair<int, int> pair = {-1, -1};
        auto matchBegin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto matchEnd = std::sregex_iterator();

        for (auto it = matchBegin; it != matchEnd; ++it) {
            int num = getNum(it->str());
            if(pair.first == -1) {
                pair.first = num;
            }
            pair.second = num;
        }
        result.push_back(pair);
    }
    return result;
}


int main() {
    const std::regex regexPattern1("[1-9]");
    const std::regex regexPattern2("([1-9]|one|two|three|four|five|six|seven|eight|nine)");
    auto lines = readFile("input.txt");
    auto intPairs = findLinesfirstLastNumber(lines, regexPattern1);
    int sum = 0;
    std::for_each(intPairs.begin(), intPairs.end(), [&](std::pair<int, int> pair) {
        std::string combination = std::to_string(pair.first) + std::to_string(pair.second);
        sum += stoi(combination);
    });
    std::cout << "Part 1 result = " << sum << "\n";

    // This part could have at least following optimization: Skip all the way the
    // letters if a number is found. This can be done because none of the numbers contain
    // another number.
    sum = 0;
    intPairs = findLinesfirstLastNumber(lines, regexPattern2);
        std::for_each(intPairs.begin(), intPairs.end(), [&](std::pair<int, int> pair) {
        std::string combination = std::to_string(pair.first) + std::to_string(pair.second);
        sum += stoi(combination);
    });
    std::cout << "Part 2 result = " << sum << "\n";
    return EXIT_SUCCESS;
}
