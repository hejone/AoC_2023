#include "card.hh"
#include <cmath>
#include <algorithm>

Card::Card(int cardNum, const std::set<int> &numbers, const std::set<int> &winNumbers) :
 _cardNum{cardNum}, _numbers{numbers}, _winNumbers{winNumbers} {}

std::set<int> readNums(const std::string& rowPart) {
    std::set<int> nums = {};
    size_t start = 0;
    auto next = rowPart.find_first_of(' ');
    while (next != std::string::npos) {
        nums.insert(std::stoi(rowPart.substr(start, next - start)));
        start = rowPart.find_first_of(_ALL_NUMS, next);
        next = rowPart.find_first_of(' ', start);
    }
    nums.insert(std::stoi(rowPart.substr(start)));
    return nums;
}

Card Card::readRow(const std::string& row)
{
    auto pos = row.find_first_of(':');
    auto i = pos - 1;
    while(isdigit(row[i])) {
        i--;
    }
    int cardNum = std::stoi(row.substr(i, pos - i));
    pos = row.find_first_of(_ALL_NUMS, pos);
    auto splitPoint = row.find_first_of('|');
    // Read both set of numbbers (remove the splitter and one space)
    std::set<int> winNumbers = readNums(row.substr(pos, splitPoint - 1 - pos));
    std::set<int> numbers = readNums(row.substr(row.find_first_of(_ALL_NUMS, splitPoint)));

    return Card(cardNum, numbers, winNumbers);
}

int Card::calcPoints()
{
    auto winNumCount = winNum();
    if (winNumCount == 0) {
        return 0;
    }
    return static_cast<int>(std::pow(2, winNumCount - 1));
}

int Card::winNum()
{
    std::set<int> interSectRes;
    std::set_intersection(_numbers.begin(), _numbers.end(),
                          _winNumbers.begin(), _winNumbers.end(),
                          std::inserter(interSectRes, interSectRes.end()));
    return interSectRes.size();
}
