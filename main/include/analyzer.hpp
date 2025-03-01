#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <iostream>
#include <string>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct analyzerState {
    bool active;        // Indicates if the analyzer is currently processing an image.
    std::string image;  // Stores the image being processed.
    double sigma;       // Time until the next event occurs.

    // Initializes the Analyzer state.
    explicit analyzerState() : active(false), image(""), sigma(std::numeric_limits<double>::infinity()) {}
};

#ifndef NO_LOGGING
// Overloads the output stream operator to display the Analyzer state.
std::ostream& operator<<(std::ostream &out, const analyzerState& state) {
    out << "State = " << state.active;
    return out;
}
#endif

class analyzer : public cadmium::Atomic<analyzerState> {
    public:
        Port<std::string> filtered_image_in;    // Input port: Receives filtered images.
        Port<std::string> analysis_report_out;  // Output port: Sends analysis report filename.
        Port<bool> done;                        // Output port: Sends "done" signal to the Filter.

        // Constructor initializes the Analyzer model.
        analyzer(const std::string& id) : cadmium::Atomic<analyzerState>(id, analyzerState()) {
            filtered_image_in = addInPort<std::string>("filtered_image_in"); // Receives filtered images.
            analysis_report_out = addOutPort<std::string>("analysis_report_out"); // Sends analysis report.
            done = addOutPort<bool>("done"); // Sends "done" signal.
        }

        // Internal Transition: Resets after processing an image.
        void internalTransition(analyzerState& state) const override {
            state.active = false;
            state.image = "";  // Clear the image name.
            state.sigma = std::numeric_limits<double>::infinity();  // Wait for the next image.
        }

        // External Transition: Processes a new filtered image if idle.
        void externalTransition(analyzerState& state, double e) const override {
            if (!filtered_image_in->empty() && !state.active) {  
                state.image = filtered_image_in->getBag().front();  // Get the first received image.
                state.active = true;
                state.sigma = 0.1;  // Process in 0.1s.
            }
        }

        // Output Function: Sends analysis report and "done" signal.
        void output(const analyzerState& state) const override {
            if (state.active) {
                std::string original_image_name = state.image.substr(9);  // Remove "filtered_".
                std::string analysis_report = original_image_name.substr(0, original_image_name.find(".")) + "_analysis_report.txt";
                analysis_report_out->addMessage(analysis_report);  // Send report filename.
                done->addMessage(true);  // Send "done" signal to the Filter.
            }
        }

        // Time Advance Function: Determines when the next event occurs.
        [[nodiscard]] double timeAdvance(const analyzerState& state) const override {
            return state.sigma;
        }
};

#endif
