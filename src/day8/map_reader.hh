#ifndef MAPREADER_HH
#define MAPREADER_HH

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

struct Node {
    std::string left;
    std::string right;

    Node(std::string _left, std::string _right) :
        left(_left), right(_right) {}
};

class MapReader {
public:
    MapReader() = default;
    ~MapReader() = default;

    void read_map(std::vector<std::string> lines);
    uint find_route(std::string starting_node = "AAA", std::string goal = "ZZZ");

private:
    std::string _instruction;
    std::unordered_map<std::string, std::unique_ptr<Node>> _map;
};

#endif
