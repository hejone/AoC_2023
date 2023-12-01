/* Solution for AoC 2023 day 1
Did this a little stupidly.
Much better solution would've been using RegEx...
*/
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <functional>

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

int isNum(const std::string& line, size_t index) {
    char curr = line[index];
    if (isdigit(curr)) {
        return static_cast<int>(curr) - 48;
    }
    return -1;
}

int isNum2(const std::string& line, size_t index) {
    char curr = line[index];
    if (isdigit(curr)) {
        return static_cast<int>(curr) - 48;
    }
    for (auto pair : LETTER_NUMS) {
        if (pair.first[0] == curr && line.size() + 1 - index >= pair.first.size()) {
            if (line.substr(index, pair.first.size()) == pair.first) {
                return pair.second;
            }
        }
    }
    return -1;
}

std::vector<std::pair<int, int>> findLinesfirstLastNumber(const std::vector<std::string>& lines,
                                                          std::function<int(std::string, size_t)> findFunc) {
    std::vector<std::pair<int, int>> result;
    result.reserve(lines.size());
    int linNum = 0;
    for (const auto& line : lines) {
        std::pair<int, int> pair = {-1, -1};
        for (size_t i = 0; i < line.size(); ++i) {
            int curr = findFunc(line, i);
            if (curr != -1) {
                if(pair.first == -1) {
                    pair.first = curr;
                }
                pair.second = curr;
            }
        }
        /* // Making sure prints
        if (linNum < 10) {
            std::cout << linNum << ": first: " << pair.first << ", last: " << pair.second << "\n";
        }
        linNum++;*/
        result.push_back(pair);
    }
    return result;
}


int main() {
    auto lines = readFile("input.txt");
    auto intPairs = findLinesfirstLastNumber(lines, isNum);
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
    intPairs = findLinesfirstLastNumber(lines, isNum2);
        std::for_each(intPairs.begin(), intPairs.end(), [&](std::pair<int, int> pair) {
        std::string combination = std::to_string(pair.first) + std::to_string(pair.second);
        sum += stoi(combination);
    });
    std::cout << "Part 2 result = " << sum << "\n";
    return EXIT_SUCCESS;
}
