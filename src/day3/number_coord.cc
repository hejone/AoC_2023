#include "number_coord.hh"

Symbol::Symbol(Coordinate coords) : coords{coords} {}
Symbol::Symbol(uint32_t x, uint32_t y) : coords{Coordinate(x, y)} {}
Symbol::Symbol(uint32_t x1, uint32_t x2, uint32_t y): coords(Coordinate(x1, x2, y)) {}

NumberCoord::NumberCoord(uint32_t x1, uint32_t x2, uint32_t y, uint32_t num) :
    Symbol(x1, x2, y), num{num} {}

SymbolChar::SymbolChar(uint32_t x, uint32_t y, char symb) :
    Symbol(x, y), symbol{symb} {}


bool NumberCoord::hasSymbol() {
    return ch != nullptr;
}
