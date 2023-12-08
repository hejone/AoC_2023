#ifndef UTIL_HH
#define UTIL_HH

#include <vector>
#include <string>
#include <fstream>
#include <inttypes.h>

namespace util {

std::vector<std::string> readFile(const std::string& filePath);
std::vector<int64_t> read_numbers_from_row(const std::string& row, char splitter = ' ');

} // namespace util

#endif // UTIL_HH
