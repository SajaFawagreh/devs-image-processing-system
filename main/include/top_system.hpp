#ifndef TOP_HPP
#define TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "loader.hpp"
#include "filterAnalyzer.hpp"

using namespace cadmium;

struct topSystem : public Coupled {
    // Output Port: Sends analysis reports
    Port<std::string> report_out;

    // Constructor initializes the top-level system with images.
    topSystem(const std::string& id, const std::vector<std::string>& images) : Coupled(id) {
        auto loader_model = addComponent<loader>("loader", images);
        auto filterAnalyzer_model = addComponent<filterAnalyzer>("filterAnalyzer");

        report_out = addOutPort<std::string>("report_out"); // Define system output port.

        // Define system couplings.
        addCoupling(loader_model->image_out, filterAnalyzer_model->in);  // Loader → FilterAnalyzer
        addCoupling(filterAnalyzer_model->out, report_out);              // FilterAnalyzer → System Output
    }
};

#endif
