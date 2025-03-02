#ifndef FILTER_ANALYZER_TESTER_HPP
#define FILTER_ANALYZER_TESTER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"
#include "../filterAnalyzer.hpp"

using namespace cadmium;

struct filterAnalyzer_tester: public Coupled {

  filterAnalyzer_tester(const std::string& id) : Coupled(id) {
    auto filterAnalyzer_model = addComponent<filterAnalyzer>("filterAnalyzer model");

    std::string test = "test1"
    std::string filter_input_test = "/absolute/path/to/devs-image-processing-system/test_files/filterAnalyzer/" + test + "/filterAnalyzer_test.txt";

    auto filterAnalyzer_file = addComponent<lib::IEStream<std::string>>(
      "filterAnalyzer file", filter_input_test
    );
    
    //Internal Couplings
    addCoupling(filterAnalyzer_file->out, filterAnalyzer_model->in); // Connect test input to FilterAnalyzer
  }

};

#endif