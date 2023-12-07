// Day 6 solution
#include <iostream>
#include <numeric>

#include "util.hh"

struct Race {
    int64_t time;
    int64_t distance;

    Race(int64_t time_, int64_t dist) {
        time = time_;
        distance = dist;
    }
};

std::vector<Race> parse_races(const std::vector<std::string>& lines) {
    auto times = util::read_numbers_from_row(
        lines.at(0).substr(lines.at(0).find_first_of(":") + 1));
    auto distances = util::read_numbers_from_row(
        lines.at(1).substr(lines.at(1).find_first_of(":") + 1));

    auto result = std::vector<Race>();
    for (size_t i = 0; i < times.size(); ++i) {
        result.push_back({times.at(i), distances.at(i)});
    }
    return result;
}

std::vector<int64_t> calc_better_than_record_times(const Race& race) {
    auto results = std::vector<int64_t>();
    int64_t time_pushed = race.time / 2;
    while (true) {
        auto dist = time_pushed * (race.time - time_pushed);
        if (dist > race.distance) {
            results.push_back(dist);
            time_pushed--;
        } else {
            break;
        }
    }
    return results;
}

int64_t find_possibilities(const std::vector<Race>& races) {
    int64_t possibilities = 1;
    for (const auto& race : races) {
        auto distances = calc_better_than_record_times(race);
        int64_t race_possibilities = distances.size() * 2;
        if (race.time % 2 == 0) {
            race_possibilities -= 1;
        }
        possibilities *= race_possibilities;
    }
    return possibilities;
}

int main() {
    auto lines = util::readFile("input.txt");
    auto races = parse_races(lines);
    auto result1 = find_possibilities(races);

    std::cout << "Part 1 result: " << result1 << "\n";

    std::pair<std::string, std::string> nums = {"", ""};
    for (const auto& race : races) {
        nums.first.append(std::to_string(race.time));
        nums.second.append(std::to_string(race.distance));
    }

    Race race2 = {stoll(nums.first), stoll(nums.second)};

    auto result2 = find_possibilities({race2});

    std::cout << "Part 2 result: " << result2 << "\n";

    return EXIT_SUCCESS;
}
