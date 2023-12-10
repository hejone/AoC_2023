#include <iostream>
#include "util.hh"
#include "oasis_report_analyzer.hh"

int main() {
    auto read_file = util::readFile("input.txt");
    auto oasis_analyzer = OasisReportAnalyzer();
    oasis_analyzer.read_report(read_file);
    auto result1 = oasis_analyzer.calculate_predictions_sum();

    std::cout << "Part 1 result: " << result1 << "\n";
    return EXIT_SUCCESS;
}
