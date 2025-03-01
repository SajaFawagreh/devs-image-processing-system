#ifndef FILTER_ANALYZER_HPP
#define FILTER_ANALYZER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "filter.hpp"
#include "analyzer.hpp"

using namespace cadmium;

struct filterAnalyzer : public Coupled {
    // Input and Output Ports
    Port<std::string> in;   // Receives images from the Loader.
    Port<std::string> out;  // Sends analysis reports.

    // Constructor initializes the FilterAnalyzer system.
    filterAnalyzer(const std::string& id) : Coupled(id) {
        auto filter_model = addComponent<filter>("filter");
        auto analyzer_model = addComponent<analyzer>("analyzer");

        // Define system input and output ports.
        in = addInPort<std::string>("in");
        out = addOutPort<std::string>("out");

        // Define couplings.
        addCoupling(in, filter_model->image_in);                                           // Loader → Filter
        addCoupling(filter_model->filtered_image_out, analyzer_model->filtered_image_in);  // Filter → Analyzer
        addCoupling(analyzer_model->done, filter_model->done);                             // Analyzer → Filter (feedback)
        addCoupling(analyzer_model->analysis_report_out, out);                             // Analyzer → System Output (send report filenames)
    }
};

#endif
