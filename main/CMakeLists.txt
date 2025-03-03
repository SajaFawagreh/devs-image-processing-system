
if(ESP_PLATFORM)
    idf_component_register( SRCS "main.cpp" "include/drivers/manchester_encoder.c"
                            REQUIRES driver
                            INCLUDE_DIRS "." "include" $ENV{CADMIUM})

    target_compile_options(${COMPONENT_LIB} PUBLIC -std=gnu++2b)
    target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
    target_compile_options(${COMPONENT_LIB} PRIVATE "-frtti")
    target_compile_options(${COMPONENT_LIB} PRIVATE "-fexceptions")
    target_compile_options(${COMPONENT_LIB} PRIVATE "-DRT_ESP32")
    # target_compile_options(${COMPONENT_LIB} PRIVATE "-DNO_LOGGING")
    # target_compile_options(${COMPONENT_LIB} PRIVATE "-DNO_LOG_STATE")
    # target_compile_options(${COMPONENT_LIB} PRIVATE "-DDEBUG_DELAY")
else()
    message(STATUS "Configuring for non-ESP32")

    # Regular CMake project setup for non-ESP32
    add_executable(Image_Processing_System main.cpp)
    add_executable(Loader_Tester test_runs/main_loader_tester.cpp)
    add_executable(Filter_Tester test_runs/main_filter_tester.cpp)
    add_executable(Analyzer_Tester test_runs/main_analyzer_tester.cpp)
    add_executable(FilterAnalyzer_Tester test_runs/main_filterAnalyzer_tester.cpp)
    add_executable(Top_System_Tester test_runs/main_top_system_tester.cpp)

    # Add required libraries and include directories
    target_include_directories(Image_Processing_System PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories(Loader_Tester PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories(Filter_Tester PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories(Analyzer_Tester PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories(FilterAnalyzer_Tester PRIVATE "." "include" $ENV{CADMIUM})
    target_include_directories(Top_System_Tester PRIVATE "." "include" $ENV{CADMIUM})

    # Non-ESP32 specific compile options
    target_compile_options(Image_Processing_System PUBLIC -std=gnu++2b)
    target_compile_options(Loader_Tester PUBLIC -std=gnu++2b)
    target_compile_options(Filter_Tester PUBLIC -std=gnu++2b)
    target_compile_options(Analyzer_Tester PUBLIC -std=gnu++2b)
    target_compile_options(FilterAnalyzer_Tester PUBLIC -std=gnu++2b)
    target_compile_options(Top_System_Tester PUBLIC -std=gnu++2b)
    
endif()
