#ifndef NUMBER_COORD
#define NUMBER_COOD

#include <memory>
#include <unordered_set>
#include <stdint.h>

class NumberCoord;
typedef std::unordered_set<std::shared_ptr<NumberCoord>> NumberSet;

struct Coordinate {
    uint32_t x1;
    uint32_t x2;
    uint32_t y;

    Coordinate(uint32_t n_x, uint32_t n_y) {
        x1 = x2 = n_x;
        y = n_y;
    }

    Coordinate(uint32_t n_x1, uint32_t n_x2, uint32_t n_y) {
        x1 = n_x1;
        x2 = n_x2;
        y = n_y;
    }
};



class Symbol {
public:
    Symbol() = delete;
    Symbol(Coordinate coords);
    Symbol(uint32_t x, uint32_t y);
    Symbol(uint32_t x1, uint32_t x2, uint32_t y);
    virtual ~Symbol() = default;

    Coordinate coords;
};

class SymbolChar : public Symbol {
public:
    SymbolChar() = delete;
    SymbolChar(uint32_t x, uint32_t y, char symb);
    virtual ~SymbolChar() = default;

    char symbol;
    NumberSet nums = NumberSet();
};

class NumberCoord: public Symbol {
public:
    NumberCoord() = delete;
    NumberCoord(uint32_t x1, uint32_t x2, uint32_t y, uint32_t num);
    virtual ~NumberCoord() = default;

    bool hasSymbol();

    uint32_t num;
    std::shared_ptr<SymbolChar> ch = nullptr;
};
#endif // NUMBER_COORD
