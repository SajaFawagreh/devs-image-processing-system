#ifndef ANALYZER_TESTER_HPP
#define ANALYZER_TESTER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"
#include "../analyzer.hpp"

using namespace cadmium;

struct analyzer_tester: public Coupled {

    // Constructor initializes the Analyzer model and connects test input files
    analyzer_tester(const std::string& id) : Coupled(id) {
        auto analyzer_model = addComponent<analyzer>("analyzer model");
        
        std::string test = "test1"
        std::string analyzer_test = "/home/sajaf/devs-image-processing-system/test_files/analyzer/" + test + "/analyzer_test.txt"

        auto analyzer_file = addComponent<lib::IEStream<std::string>>(
            "analyzer file", analyzer_test
        );

        // Internal Couplings
        addCoupling(analyzer_file->out, analyzer_model->filtered_image_in); // Connect test input to Analyzer
    }
};

#endif