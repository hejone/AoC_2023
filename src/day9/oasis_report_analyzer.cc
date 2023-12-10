#include "oasis_report_analyzer.hh"
#include "util.hh"

Report::Report(const std::vector<int64_t>& report)
    {
        original = std::deque<int64_t> {report.begin(), report.end()};
    }

int64_t Report::calculate_prediction() {
    auto rows = std::deque<std::deque<int64_t>>();
    auto current_row = original;
    rows.push_back(original);
    while(true) {
        auto next_row = std::deque<int64_t>();
        bool all_zeros = true;
        for (size_t i = 0; i < current_row.size() - 1; ++i) {
            int64_t next_num = current_row.at(i + 1) - current_row.at(i);
            next_row.push_back(next_num);
            all_zeros &= next_num == 0;
        }
        rows.push_back(next_row);
        if (all_zeros) {
            break;
        }
        current_row = next_row;
    }
    for (size_t i = rows.size() - 1; i > 0; --i) {
        auto next = rows.at(i).back() + rows.at(i - 1).back();
        rows.at(i - 1).push_back(next);
    }
    return rows.at(0).back();
}

void OasisReportAnalyzer::read_report(const std::vector<std::string>& lines) {
    for (const auto& row : lines) {
        auto line = util::read_numbers_from_row(row);
        _reports.push_back(std::make_unique<Report>(line));
    }
}

int64_t OasisReportAnalyzer::calculate_predictions_sum()
{
    int64_t sum = 0;
    for (const auto& report : _reports) {
        sum += report->calculate_prediction();
    }
    return sum;
}
