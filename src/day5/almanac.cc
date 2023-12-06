#include <algorithm>
#include <iostream>
#include "almanac.hh"

std::vector<int64_t> read_numbers_from_row(const std::string& row, char splitter = ' ') {
    auto result = std::vector<int64_t>();
    size_t start_it = 0;
    auto end_it = row.find_first_of(splitter);
    while(end_it != std::string::npos) {
        result.push_back(std::atoll(row.substr(start_it, end_it - start_it).c_str()));
        start_it = end_it + 1;
        end_it = row.find_first_of(splitter, start_it);
    }
    result.push_back(std::atoi(row.substr(start_it).c_str()));
    return result;
}

std::pair<std::string, std::string> parse_header(const std::string& header) {
    auto result = std::pair<std::string, std::string> {"", ""};
    auto first_dash = header.find_first_of('-');
    result.first = header.substr(0, first_dash);
    auto second_dash = header.find_first_of('-', first_dash + 1);
    result.second = header.substr(second_dash + 1,
                                  header.find_first_of(' ', second_dash + 1) - second_dash - 1);
    return result;
}

void Almanac::read_input(const std::vector<std::string>& input)
{
    // First line is seeds as "Seeds: (\d+)+"
    auto seeds_str = input.at(0).substr(input.at(0).find_first_of(':') + 2);
    _seeds = read_numbers_from_row(seeds_str);
    // The actual almanac starts from line 3 (index 2)
    for (size_t i = 2; i < input.size(); ++i) {
        auto s_and_d = parse_header(input.at(i));
        auto row = std::string("\n");
        auto ranges = std::vector<std::shared_ptr<Range>>();
        do {
            ++i;
            if(i >= input.size() || (row = input.at(i)) == "") {
                break;
            }
            auto nums = read_numbers_from_row(row); // This always has three numbers
            ranges.push_back(std::make_shared<Range>(nums[0], nums[1], nums[2]));
        } while (true);

        auto s_d_mapping = SourceDestMapping(s_and_d.first, s_and_d.second, ranges);
        _by_source_mapping.insert({s_and_d.first, s_d_mapping});
    }
}

int64_t Almanac::find_smallest_location(int64_t start, int64_t range)
{
    std::string end = "location";
    int64_t min_value = std::numeric_limits<int64_t>::max();
    for (auto seed = start; seed < start + range; ++seed) {
        std::string current_source = "seed";
        auto current_value = seed;
        auto range_mapping = &_by_source_mapping.at(current_source);
        while(true) {
            for (const auto& range : range_mapping->ranges) {
                if (range->is_in_range(current_value)) {
                    current_value += range->difference;
                    break;
                }
            }
            current_source = range_mapping->destination;
            if (current_source == end) {
                break;
            }
            range_mapping = &_by_source_mapping.at(current_source);
        }
        min_value = std::min(current_value, min_value);
    }
    return min_value;
}

int64_t Almanac::find_smallest_location_indv_seeds()
{
    auto min_value = std::numeric_limits<int64_t>::max();
    for(const auto& seed : _seeds) {
        min_value = std::min(find_smallest_loc_ranges(min_value, seed, 0, "seed"), min_value);
    }
    return min_value;
}

int64_t Almanac::find_smallest_location_ranges()
{
    auto values = std::vector<int64_t>();
    for(size_t i = 0; i < _seeds.size(); i += 2) {
        values.push_back(find_smallest_loc_ranges(std::numeric_limits<int64_t>::max(), _seeds[i], _seeds[i+1], "seed"));
    }
    return *std::min_element(values.begin(), values.end());
}

int64_t Almanac::find_smallest_loc_ranges(int64_t curr_min, int64_t range_start, int64_t length, std::string source) {
    if(source == "location") {
        curr_min = std::min(range_start, curr_min);
        return curr_min;
    }
    std::vector<std::shared_ptr<SimpleRange>> ranges = {std::make_shared<SimpleRange>(range_start, length)};
    auto range_mapping = &_by_source_mapping.at(source);
    while(!ranges.empty()) {
        auto curr_range = ranges.back();
        ranges.pop_back();
        auto target_ranges = range_mapping->ranges;
        bool found_range = false;
        for(size_t i = 0; i < target_ranges.size(); ++i) {
            auto shared_range = curr_range->part_in_range(*target_ranges[i]);
            if (shared_range != SimpleRange::NOT_FOUND) {
                found_range = true;
                if (shared_range.first != curr_range->start) {
                    // The left edge has of new range has to be at start of the current range.
                    // The right edge is one before the start of the shared range,
                    // thus cutting of one from the length makes new range correct
                    ranges.push_back(std::make_shared<SimpleRange>(curr_range->start,
                                                                   shared_range.first - curr_range->start - 1));

                }
                if (shared_range.second != curr_range->end) {
                    // Here the left edge is one after the shared range end and
                    // right edge is the right edge of the current range. Thus left has to
                    // start one after shared range and length has to be one shorter as well
                    // to not go over right edge.
                    ranges.push_back(std::make_shared<SimpleRange>(shared_range.second + 1,
                                                                   curr_range->end - shared_range.second - 1));
                }
                auto translated_range_start = target_ranges[i]->translate(shared_range.first);
                curr_min = std::min(find_smallest_loc_ranges(curr_min, translated_range_start,
                                                             shared_range.second - shared_range.first,
                                                             range_mapping->destination), curr_min);
                if (curr_range->start == shared_range.first && curr_range->end == shared_range.second) {
                    break;
                }
            }
        }
        if (!found_range) {
            curr_min = std::min(find_smallest_loc_ranges(curr_min, curr_range->start,
                                                         curr_range->end - curr_range->start,
                                                         range_mapping->destination), curr_min);
        }
    }
    return curr_min;
}
