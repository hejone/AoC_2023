#ifndef COORD_HANDLER
#define COORD_HANDLER

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <stdint.h>

#include "number_coord.hh"

typedef std::vector<std::shared_ptr<NumberCoord>> NumVec;
typedef std::vector<std::shared_ptr<SymbolChar>> SymbolVec;
typedef std::vector<std::vector<std::shared_ptr<Symbol>>> PtrMap;

class CoordHandler {
public:
    CoordHandler() = delete;
    CoordHandler(const std::vector<std::string>& map);
    ~CoordHandler() = default;

    void readMap(const std::vector<std::string>& map,
                 SymbolVec& symbsRef, NumVec& numsRef, PtrMap& ptrMapRef);

    int calcPartSum();

    int calcGearRatioSum();

private:
    NumVec m_numCoords = NumVec();
    SymbolVec m_symbols = SymbolVec();
    PtrMap m_map = PtrMap();
};

#endif // COORD_HANDLER
