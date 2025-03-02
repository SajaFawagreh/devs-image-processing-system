#ifndef FILTERER_TESTER_HPP
#define FILTERER_TESTER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"
#include "../filter.hpp"

using namespace cadmium;

struct filter_tester: public Coupled {

    // Constructor initializes the Filter model and connects test input files
    filter_tester(const std::string& id) : Coupled(id) {
        auto filter_model = addComponent<filter>("filter model");

        std::string test = "test1"
        std::string filter_input_test = "/absolute/path/to/devs-image-processing-system/test_files/filter/" + test + "/filter_input_test.txt";
        std::string filter_done_signal_test = "/absolute/path/to/devs-image-processing-system/test_files/filter/" + test + "/filter_done_signal_test.txt";

        auto filter_input_file = addComponent<lib::IEStream<std::string>>(
            "filter input file", filter_input_test
        );
        auto filter_done_signal_file = addComponent<lib::IEStream<bool>>(
            "filter done signal file", filter_done_signal_test
        );

        // Internal Couplings
        addCoupling(filter_input_file->out, filter_model->image_in);   // Connect test input to Filter
        addCoupling(filter_done_signal_file->out, filter_model->done); // Connect test "done" signals
    }
};

#endif