#ifndef FILTER_ANALYZER_TESTER_HPP
#define FILTER_ANALYZER_TESTER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"
#include "../filterAnalyzer.hpp"

using namespace cadmium;

struct filterAnalyzer_tester: public Coupled {

  filterAnalyzer_tester(const std::string& id) : Coupled(id) {
    auto filterAnalyzer_model = addComponent<filterAnalyzer>("filterAnalyzer model");
    auto filterAnalyzer_file = addComponent<lib::IEStream<std::string>>("filterAnalyzer file", "/home/sajaf/devs-image-processing-system/test_files/filterAnalyzer/test1/filterAnalyzer_test.txt");
    
    //Internal Couplings
    addCoupling(filterAnalyzer_file->out, filterAnalyzer_model->in); // Connect test input to FilterAnalyzer
  }

};

#endif