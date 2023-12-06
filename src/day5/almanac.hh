#ifndef ALMANAC_HH
#define ALMANAC_HH

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <limits>

#include <inttypes.h>

struct Range {
    int64_t start;
    int64_t end;
    int64_t difference;

    bool inline is_in_range(int64_t num) {
        return num >= start && num <= end;
    }

    int64_t inline translate(int64_t to_translate) {
        return to_translate + difference;
    }

    Range(int64_t d_start, int64_t s_start, int64_t length) {
        start = s_start;
        end = start + length - 1; // 0 indexed
        difference = d_start - s_start;
    }
};

struct SimpleRange {
    int64_t start;
    int64_t end;

    static inline std::pair<int64_t, int64_t> NOT_FOUND =
      std::pair<int64_t, int64_t> {std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max()};

    std::pair<int64_t, int64_t> part_in_range(Range t_range) {
        int64_t min_val = std::max(start, t_range.start);
        int64_t max_val = std::min(end, t_range.end);
        if (min_val <= max_val) {
            return {min_val, max_val};
        }
        return NOT_FOUND;
    }

    SimpleRange(int64_t start_, int64_t length) {
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
    int64_t find_smallest_location(int64_t start, int64_t range);
    int64_t find_smallest_location_indv_seeds();
    int64_t find_smallest_location_ranges();

private:
    std::vector<int64_t> _seeds = {};
    std::unordered_map<std::string, SourceDestMapping> _by_source_mapping = {};

    int64_t find_smallest_loc_ranges(int64_t curr_min, int64_t range_start,
                                      int64_t length, std::string source);
};

#endif // ALMANAC_HH
