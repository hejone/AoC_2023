#include <algorithm>
#include <numeric>
#include "coord_handler.hh"

CoordHandler::CoordHandler(const std::vector<std::string>& map) {
    m_symbols.clear();
    m_numCoords.clear();
    m_map.clear();
    readMap(map, m_symbols, m_numCoords, m_map);
}

void CoordHandler::readMap(const std::vector<std::string>& map,
    SymbolVec& symbsRef, NumVec& numsRef, PtrMap& ptrMapRef) {
    size_t y = 0;
    for (const auto& row : map) {
        auto ptrRow = std::vector<std::shared_ptr<Symbol>>();
        for(size_t x = 0; x < row.size(); ++x) {
            if(row.at(x) == '.') {
                ptrRow.push_back(nullptr);
            }
            else if (isdigit(row.at(x))) {
                int start = x;
                while(x < row.size() && isdigit(row.at(x))) {
                    ++x;
                }
                int num = std::stoi(row.substr(start, x));
                auto numCoord = std::make_shared<NumberCoord>(start, x - 1, y, num);
                numsRef.push_back(numCoord);
                for (size_t i = start; i < x; ++i) {
                    ptrRow.push_back(numCoord);
                }
                x--;
            }
            else {
                auto symbPtr = std::make_shared<SymbolChar>(x, y, row.at(x));
                symbsRef.push_back(symbPtr);
                ptrRow.push_back(symbPtr);
            }
        }
        y++;
        ptrMapRef.push_back(ptrRow);
    }

    uint32_t yxMin = 0;
    uint32_t yMax = ptrMapRef.size() - 1;
    uint32_t xMax = ptrMapRef.front().size() - 1;
    // Link symbols to all numbers
    for (auto const& symPtr : symbsRef) {
        auto xLimits = std::pair<int, int> {
            std::max(symPtr->coords.x1 - 1, yxMin),
            std::min(symPtr->coords.x1 + 1, xMax)
        };
        auto yLimits = std::pair<int, int> {
            std::max(symPtr->coords.y - 1, yxMin),
            std::min(symPtr->coords.y + 1, yMax)
        };
        for (auto i = yLimits.first; i <= yLimits.second; ++i) {
            for (auto j = xLimits.first; j <= xLimits.second; ++j) {
                auto current = ptrMapRef[i][j];
                if(current != nullptr) {
                    auto numPtr = std::dynamic_pointer_cast<NumberCoord>(current);
                    if (numPtr != nullptr) {
                        numPtr->ch = symPtr;
                        symPtr->nums.insert(numPtr);
                    }
                }
            }
        }
    }
}

int  CoordHandler::calcPartSum() {
    uint32_t sum = 0;
    for (auto const& numPtr : m_numCoords) {
        if(numPtr->hasSymbol()) {
            sum += numPtr->num;
        }
    }
    return sum;
}

int CoordHandler::calcGearRatioSum() {
    int32_t sum = 0;
    for (auto const& symPtr : m_symbols) {
        if (symPtr->symbol != '*') {
            continue;
        }
        if(symPtr->nums.size() == 2) {
            sum += std::accumulate(symPtr->nums.begin(), symPtr->nums.end(), 1,
            [] (int32_t res, std::shared_ptr<NumberCoord> curr) {
                return res * curr->num;
            });
        }
    }
    return sum;
}
