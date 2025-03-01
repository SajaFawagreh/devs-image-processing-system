#ifndef LOADER_TESTER_HPP
#define LOADER_TESTER_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"
#include "../loader.hpp"

using namespace cadmium;

struct loader_tester: public Coupled {

    // Constructor initializes the Loader with a list of images
    loader_tester(const std::string& id, const std::vector<std::string>& images) : Coupled(id) {
        auto loader_model = addComponent<loader>("loader model", images);
    }
};

#endif
