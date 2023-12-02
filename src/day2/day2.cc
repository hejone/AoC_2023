/* AoC 2023 Day 2 solution */
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include <map>
#include <iostream>
#include <numeric>

typedef std::array<int, 3> RGBTuple;

std::pair<int, std::vector<RGBTuple>> splitLine(const std::string& line) {
    auto pos = line.find_first_of(':');
    auto index = pos - 1;
    while (isdigit(line[index])) {
        index--;
    }
    int gameNum = std::atoi(line.substr(index, pos - index).c_str());
    std::vector<std::string> rgbSrings;
    std::string rawRgbStrings = line.substr(pos + 2); // Remove both the colon and one space
    index = rawRgbStrings.find_first_of(';');
    while(index != std::string::npos) {
        rgbSrings.push_back(rawRgbStrings.substr(0, index));
        rawRgbStrings = rawRgbStrings.substr(index + 2);
        index = rawRgbStrings.find_first_of(';');
    }
    rgbSrings.push_back(rawRgbStrings);

    std::vector<RGBTuple> rgbs;
    for (const auto& rgbString : rgbSrings) {
        RGBTuple trio = {0,0,0};
        for (size_t i = 0; i < rgbString.size(); ++i) {
            if(!isdigit(rgbString[i])) {
                continue;
            }
            auto num_start = i;
            while(isdigit(rgbString[i])) {
                ++i;
            }
            int num = std::atoi(rgbString.substr(num_start, i).c_str());
            ++i; // Go over the space between the number and colour
            switch (rgbString[i]) {
            case 'r':
                trio[0] = num;
                break;
            case 'g':
                trio[1] = num;
                break;
            case 'b':
                trio[2] = num;
                break;
            default:
                break;
            }
        }
        rgbs.push_back(trio);
    }
    return std::pair<int, std::vector<RGBTuple>> {gameNum, rgbs};
}

std::map<int, std::vector<RGBTuple>> readFile(const std::string& filePath) {
    std::ifstream input(filePath);
    auto outputMap = std::map<int, std::vector<RGBTuple>>();
    if (!input.is_open()) {
        return outputMap;
    }
    std::string line;
    while(std::getline(input, line)) {
        outputMap.insert(splitLine(line));
    }
    return outputMap;
}

int calcSucceededSum(const std::map<int, std::vector<RGBTuple>>& rgbMapping,
                     int redLimit = 12, int greenLimit = 13, int blueLimit = 14) {
    int succeeded_sum = 0;
    for (const auto& [game_num, rgbs] : rgbMapping) {
        bool succeeded = true;
        for (const auto& rgb : rgbs) {
            if (rgb[0] > redLimit || rgb[1] > greenLimit || rgb[2] > blueLimit) {
                succeeded = false;
                break;
            }
        }
        if (succeeded) {
            succeeded_sum += game_num;
        }
    }
    return succeeded_sum;
}

int calcMinimumPossiblePowersSum(const std::map<int, std::vector<RGBTuple>>& rgbMapping) {
    int total_sum = 0;
    for (const auto& [game_num, rgbs] : rgbMapping) {
        RGBTuple minimums = {-1, -1, -1};
        for (const auto& rgb : rgbs) {
            for (size_t i = 0; i < 3; ++i) {
                minimums[i] = std::max(minimums[i], rgb[i]);
            }
        }
        total_sum += std::accumulate(minimums.begin(), minimums.end(), 1, std::multiplies<int>());
    }
    return total_sum;
}

int main() {
    auto mapping = readFile("input.txt");
    int succeeded_sum = calcSucceededSum(mapping);
    std::cout << "Part 1: " << succeeded_sum << "\n";

    int power_sum = calcMinimumPossiblePowersSum(mapping);
    std::cout << "Part 2: " << power_sum << "\n";

    return EXIT_SUCCESS;
}
