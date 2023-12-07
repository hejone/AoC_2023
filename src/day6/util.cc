#include "util.hh"

std::vector<std::string> util::readFile(const std::string& filePath) {
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

std::vector<int64_t> util::read_numbers_from_row(const std::string& row, char splitter) {
    std::string nums = "0123456789";
    auto result = std::vector<int64_t>();
    size_t start_it = row.find_first_of(nums);
    auto end_it = row.find_first_of(splitter, start_it);
    while(end_it != std::string::npos) {
        result.push_back(std::atoll(row.substr(start_it, end_it - start_it).c_str()));
        start_it = row.find_first_of(nums, end_it);
        end_it = row.find_first_of(splitter, start_it);
    }
    result.push_back(std::atoi(row.substr(start_it).c_str()));
    return result;
}
