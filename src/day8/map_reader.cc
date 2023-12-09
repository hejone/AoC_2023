#include "map_reader.hh"

void MapReader::read_map(std::vector<std::string> lines) {
    _instruction = lines.front();

    auto map_rows = std::vector<std::string>(lines.begin() + 2, lines.end());

    for (const auto& row : map_rows) {
        std::string source = row.substr(0, row.find_first_of(' '));
        std::string left = row.substr(row.find_first_of('(') + 1, 3);
        std::string right = row.substr(row.find_last_of(')') - 3, 3);
        _map.insert({source, std::make_unique<Node>(left, right)});
    }
}

uint MapReader::find_route(std::string starting_node, std::string goal)
{
    uint steps = 0;
    uint ip = 0;
    size_t instr_len = _instruction.size();
    auto current = starting_node;
    while(true) {
        if (current == goal) {
            break;
        }
        ++steps;
        if(_instruction.at(ip) == 'R') {
            current = _map.at(current)->right;
        }
        else {
            current = _map.at(current)->left;
        }
        ip = steps % instr_len;
    }
    return steps;
}
