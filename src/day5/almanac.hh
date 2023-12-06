#ifndef ALMANAC_HH
#define ALMANAC_HH

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <limits>

#include <inttypes.h>

struct Range {
    uint64_t start;
    uint64_t end;
    uint64_t difference;
    bool direction;

    bool inline is_in_range(uint64_t num) {
        return num >= start && num <= end;
    }

    uint64_t inline translate(uint64_t to_translate) {
        if(direction) {
            return to_translate + difference;
        }
        return to_translate - difference;
    }

    Range(uint64_t d_start, uint64_t s_start, uint64_t length) {
        start = s_start;
        end = start + length - 1; // 0 indexed
        if (d_start > s_start) {
            difference = d_start - s_start;
            direction = true;
        }
        else {
            difference = s_start - d_start;
            direction = false;
        }
    }
};

struct SimpleRange {
    uint64_t start;
    uint64_t end;

    static inline std::pair<uint64_t, uint64_t> WRONG_PAIR =
      std::pair<uint64_t, uint64_t> {std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint64_t>::max()};

    std::pair<uint64_t, uint64_t> part_in_range(Range t_range) {
        uint64_t min_val = std::max(start, t_range.start);
        uint64_t max_val = std::min(end, t_range.end);
        if (min_val <= max_val) {
            return {min_val, max_val};
        }
        return WRONG_PAIR;
    }

    SimpleRange(uint64_t start_, uint64_t length) {
        start = start_;
        end = start + length;
    }
};

struct SourceDestMapping {
    std::string source;
    std::string destination;

    std::vector<std::shared_ptr<Range>> ranges;

    SourceDestMapping(const std::string& source_, const std::string& dest,
                      const std::vector<std::shared_ptr<Range>>& rangs) {
        source = source_;
        destination = dest;
        ranges = rangs;
    }
};

class Almanac {
public:
    Almanac() = default;
    ~Almanac() = default;

    void read_input(const std::vector<std::string>& input);
    uint64_t find_smallest_location(uint64_t start, uint64_t range);
    uint64_t find_smallest_location_indv_seeds();
    uint64_t find_smallest_location_ranges();

private:
    std::vector<uint64_t> _seeds = {};
    std::unordered_map<std::string, SourceDestMapping> _by_source_mapping = {};

    uint64_t find_smallest_loc_ranges(uint64_t curr_min, uint64_t range_start,
                                      uint64_t length, std::string source);
};

#endif // ALMANAC_HH
