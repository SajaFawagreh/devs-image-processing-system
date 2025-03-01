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
        auto filter_input_file = addComponent<lib::IEStream<std::string>>(
            "filter input file", "/home/sajaf/devs-image-processing-system/test_files/filter/test1/filter_input_test.txt"
        );
        auto filter_done_signal_file = addComponent<lib::IEStream<bool>>(
            "filter done signal file", "/home/sajaf/devs-image-processing-system/test_files/filter/test1/filter_done_signal_test.txt"
        );

        // Internal Couplings
        addCoupling(filter_input_file->out, filter_model->image_in);   // Connect test input to Filter
        addCoupling(filter_done_signal_file->out, filter_model->done); // Connect test "done" signals
    }
};

#endif