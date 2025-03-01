#include <limits>
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"
#include "include/devs_tests/loader_tester.hpp"

using namespace cadmium;

int main() {

	std::vector<std::string> image_list = {"image1.jpeg", "image2.jpeg"};

	auto model = std::make_shared<loader_tester> ("loader tester", image_list);
	auto rootCoordinator = RootCoordinator(model);

	rootCoordinator.setLogger<STDOUTLogger>(";");
	// rootCoordinator.setLogger<CSVLogger>("loader_test_output.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(15.0);
	rootCoordinator.stop();	

	return 0;
}