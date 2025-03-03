#ifndef TOP_SYSTEM_TESTER_HPP
#define TOP_SYSTEM_TESTER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"
#include "../top_system.hpp"

using namespace cadmium;

struct top_system_tester: public Coupled {

    // Constructor initializes the Loader with a list of images
    top_system_tester(const std::string& id, const std::vector<std::string>& images) : Coupled(id) {
        auto top_model = addComponent<topSystem>("top model", images);
    }
};

#endif
