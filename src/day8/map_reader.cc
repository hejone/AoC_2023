#include "map_reader.hh"
#include <iostream>
#include <numeric>

void MapReader::read_map(std::vector<std::string> lines) {
    _instruction = lines.front();

    auto map_rows = std::vector<std::string>(lines.begin() + 2, lines.end());

    for (const auto& row : map_rows) {
        std::string source = row.substr(0, row.find_first_of(' '));
        std::string left = row.substr(row.find_first_of('(') + 1, 3);
        std::string right = row.substr(row.find_last_of(')') - 3, 3);
        _map.insert({source, std::make_unique<Node>(left, right)});
        if (source.back() == 'A') {
            _paths.push_back(Path(source));
        }
    }
}

uint MapReader::find_route(std::string starting_node, std::string goal) {
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

uint64_t MapReader::find_all_routes_intersection_point() {
    uint steps = 0;
    auto inst_len = _instruction.size();
    for (auto& path : _paths) {
        steps = 0;
        int count = 0;
        while (true) {
            auto instr = _instruction.at(steps % inst_len);
            steps++;
            if (move_one(path, instr)) {
                path.cycle_len = steps;
                break;
            }
        }
    }
    uint64_t total_steps = _paths.front().cycle_len;
    for (size_t i = 1; i < _paths.size(); ++i) {
        total_steps = std::lcm(total_steps, static_cast<uint64_t>(_paths.at(i).cycle_len));
    }
    return total_steps;
}

bool MapReader::move_one(Path& path, char instr) {
    if (instr == 'R') {
        path.current = _map.at(path.current)->right;
    } else {
        path.current = _map.at(path.current)->left;
    }
    if (path.current.back() == 'Z') {
        return true;
    }
    return false;
}
