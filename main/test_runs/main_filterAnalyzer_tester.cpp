#include <limits>
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"
#include "include/devs_tests/filterAnalyzer_tester.hpp"

using namespace cadmium;

int main() {

	auto model = std::make_shared<filterAnalyzer_tester> ("filterAnalyzer tester");
	auto rootCoordinator = RootCoordinator(model);

	rootCoordinator.setLogger<STDOUTLogger>(";");
	// rootCoordinator.setLogger<CSVLogger>("analyzer_test_output.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(20.0);
	rootCoordinator.stop();	

	return 0;
}