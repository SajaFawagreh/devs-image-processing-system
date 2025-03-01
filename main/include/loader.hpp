#ifndef LOADER_HPP
#define LOADER_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "cadmium/modeling/devs/atomic.hpp"

struct loaderState {
    bool active;                          // Indicates if the Loader is currently active.
    std::queue<std::string> image_queue;  // Queue storing images to be processed.
    double sigma;                         // Time until the next event occurs.

    // Initializes the Loader state with a list of images.
    explicit loaderState(const std::vector<std::string>& images) 
        : active(!images.empty()), sigma(images.empty() ? std::numeric_limits<double>::infinity() : 5.0) {
        for (const auto& img : images) {
            image_queue.push(img);
        }
    }
};

#ifndef NO_LOGGING
// Overloads the output stream operator to display the Loader state.
std::ostream& operator<<(std::ostream &out, const loaderState& state) {
    out << "State = " << state.active;
    return out;
}
#endif

using namespace cadmium;

class loader : public cadmium::Atomic<loaderState> {
public:
    Port<std::string> image_out;  // Output port: Sends images.

    // Constructor initializes the Loader with a list of image filenames.
    loader(const std::string& id, const std::vector<std::string>& images) 
        : cadmium::Atomic<loaderState>(id, loaderState(images)) {
            image_out = addOutPort<std::string>("image_out");  
    }

    // Internal Transition: Removes the processed image from the queue and schedules the next one.
    // If no images remain, the Loader deactivates.
    void internalTransition(loaderState& state) const override {
        if (!state.image_queue.empty()) {
            state.image_queue.pop();  // Remove the sent image.
        }

        // If there are more images, schedule the next one.
        if (!state.image_queue.empty()) {
            state.sigma = 5.0;  // Schedule the next image in 5 seconds.
        } else {
            state.active = false;  
            state.sigma = std::numeric_limits<double>::infinity();  // Stop if queue is empty.
        }
    }

    // External Transition: Not needed since the Loader does not process external events.
    void externalTransition(loaderState& state, double e) const override {
        // No external event processing.
    }

    // Output Function: Sends the next image to Filter after converting it from .jpg to .png.
    void output(const loaderState& state) const override {
        if (!state.image_queue.empty()) {
            std::string jpeg_image = state.image_queue.front();
            std::string png_image = jpeg_image.substr(0, jpeg_image.find_last_of(".")) + ".png"; // Convert to .png
            image_out->addMessage(png_image);
        }
    }

    // Time Advance Function: Determines when the next event occurs based on the Loader state.
    double timeAdvance(const loaderState& state) const override {
        return state.sigma;
    }
};

#endif
