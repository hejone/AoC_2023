#ifndef OASIS_ANALYZER
#define OASIS_ANALYZER

#include <deque>
#include <vector>
#include <string>
#include <memory>
#include <inttypes.h>

struct Report {
    std::deque<int64_t> original;

    Report(const std::vector<int64_t>& report);

    int64_t calculate_prediction();
};

class OasisReportAnalyzer {
public:
    OasisReportAnalyzer() = default;
    ~OasisReportAnalyzer() = default;

    void read_report(const std::vector<std::string>& lines);
    int64_t calculate_predictions_sum();

private:
    std::vector<std::unique_ptr<Report>> _reports = {};
};

#endif
