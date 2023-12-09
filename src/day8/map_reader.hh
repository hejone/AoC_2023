#ifndef MAPREADER_HH
#define MAPREADER_HH

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <inttypes.h>

struct Node {
    std::string left;
    std::string right;

    Node(std::string _left, std::string _right) :
        left(_left), right(_right) {}
};

struct Path {
    std::string current;
    uint cycle_len = 0;

    Path(std::string start) {
        current = start;
    }
};

class MapReader {
public:
    MapReader() = default;
    ~MapReader() = default;

    void read_map(std::vector<std::string> lines);
    uint find_route(std::string starting_node = "AAA", std::string goal = "ZZZ");
    uint64_t find_all_routes_intersection_point();

private:
    std::string _instruction;
    std::unordered_map<std::string, std::unique_ptr<Node>> _map;
    std::vector<Path> _paths;

    bool move_one(Path& path, char instr);
};

#endif
