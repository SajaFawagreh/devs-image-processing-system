#ifndef FILTER_HPP
#define FILTER_HPP

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include <queue>
#include <string>

using namespace cadmium;

struct filterState {
    std::queue<std::string> image_queue;  // Queue storing images to be processed.
    bool active;                          // Indicates if the Filter is currently active.
    double sigma;                         // Time until the next event occurs.
    bool done_received;                   // True when the analyzer has completed processing the last image.

    // Initializes the Filter state.
    explicit filterState() : active(false), sigma(std::numeric_limits<double>::infinity()) {}
};

#ifndef NO_LOGGING
// Overloads the output stream operator to display the Filter state.
std::ostream& operator<<(std::ostream &out, const filterState& state) {
    out << "State = " << state.active;
    return out;
}
#endif

class filter : public cadmium::Atomic<filterState> {
public:
    Port<std::string> image_in;            // Input port: Receives raw images.
    Port<std::string> filtered_image_out;  // Output port: Sends filtered images.
    Port<bool> done;                       // Input port: Receives "done" signal from the Analyzer.

    // Constructor initializes the Filter model.
    filter(const std::string& id) : cadmium::Atomic<filterState>(id, filterState()) {
        image_in = addInPort<std::string>("image_in");  // Receives raw images.
        filtered_image_out = addOutPort<std::string>("out");  // Sends filtered images.
        done = addInPort<bool>("done");  // Receives "done" signal.
    }

    // Internal Transition: Removes the processed image and waits for the next one.
    void internalTransition(filterState& state) const override {
        if (!state.image_queue.empty()) {
            state.image_queue.pop();  // Remove the processed image.
        }

        // The filter deactivates and waits for the next "done" signal.
        state.active = false;
        state.sigma = std::numeric_limits<double>::infinity();  // Wait for new images.
    }

    // External Transition: Handles incoming images and "done" signals.
    void externalTransition(filterState& state, double e) const override {
        // If a new image arrives, store it in the queue.
        if (!image_in->empty()) {
            std::string image = image_in->getBag().back();
            state.image_queue.push(image);
        }

        // If a "done" signal is received, allow the next image to be processed.
        if (!done->empty()) {
            bool msg = done->getBag().back();
            if (msg) {
                state.done_received = true;  // Mark as ready for the next image.
            }
        }

        // Start processing the next image only if the previous image is done.
        if (!state.image_queue.empty() && state.done_received && !state.active) {
            state.active = true;
            state.done_received = false;  // Reset done flag.
            state.sigma = 0.1;  // Process in 0.1s.
        }
    }

    // Output Function: Sends the processed image to the Analyzer.
    void output(const filterState& state) const override {
        if (state.active && !state.image_queue.empty()) {
            std::string filtered_image = "filtered_" + state.image_queue.front();  // Get the first image.
            filtered_image_out->addMessage(filtered_image);
        }
    }

    // Time Advance Function: Determines when the next event occurs.
    [[nodiscard]] double timeAdvance(const filterState& state) const override {
        return state.sigma;
    }
};

#endif
