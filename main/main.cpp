#include "cadmium/simulation/rt_root_coordinator.hpp"
#include "cadmium/simulation/root_coordinator.hpp"
#include <limits>
#include "include/top_system.hpp"

#ifdef RT_ESP32
	#include <cadmium/simulation/rt_clock/ESPclock.hpp>
#else
	#include <cadmium/simulation/rt_clock/chrono.hpp>
#endif

#ifndef NO_LOGGING
	#include "cadmium/simulation/logger/stdout.hpp"
	#include "cadmium/simulation/logger/csv.hpp"
#endif

using namespace cadmium;

extern "C" {
	#ifdef RT_ESP32
		void app_main() //starting point for ESP32 code
	#else
		int main()		//starting point for simulation code
	#endif
	{

		std::vector<std::string> image_list = {"image1.jpeg", "image2.jpeg", "image3.jpeg", "image4.jpeg"};

		std::shared_ptr<topSystem> model = std::make_shared<topSystem> ("topSystem", image_list);

		#ifdef RT_ESP32
			cadmium::ESPclock clock;
			auto rootCoordinator = cadmium::RealTimeRootCoordinator<cadmium::ESPclock<double>>(model, clock);
		#else
			cadmium::ChronoClock clock;
			auto rootCoordinator = cadmium::RealTimeRootCoordinator<cadmium::ChronoClock<std::chrono::steady_clock>>(model, clock);

			// auto rootCoordinator = cadmium::RootCoordinator(model);
		#endif

		#ifndef NO_LOGGING
		rootCoordinator.setLogger<cadmium::STDOUTLogger>(";");
		//rootCoordinator.setLogger<cadmium::CSVLogger>("trafficLightLog.csv", ";");
		#endif

		rootCoordinator.start();

		#ifdef RT_ESP32
		rootCoordinator.simulate(std::numeric_limits<double>::infinity());
		#else
		rootCoordinator.simulate(25.0);
		#endif

		rootCoordinator.stop();

		#ifndef RT_ESP32
						return 0;
		#endif
	}
}

