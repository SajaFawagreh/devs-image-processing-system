# Image Processing System - DEVS Model

## Introduction
This repository implements the **Image Processing System** using the **Cadmium DEVS framework**. The system simulates an automated image processing workflow where images are loaded, filtered, and analyzed sequentially. 

The **Loader** initializes with a list of images, converts them to `.png`, and sends them for processing. The **Filter** processes the images and forwards them to the **Analyzer**, which generates analysis reports. 

The system is structured using **atomic** and **coupled DEVS models**, ensuring modular and event-driven execution.

## Repository Structure
This repository is arranged in the following manner:

```sh
.
├── bin/                         # Compiled executables for running the models
├── build/                       # Build directory (generated after compilation)
├── main/                        # Main source code directory
│   ├── include/                 # Header files for models and tests
│   │   ├── devs_tests/          # Test models for individual components
│   │   │   ├── analyzer_tester.hpp
│   │   │   ├── filter_tester.hpp
│   │   │   ├── filterAnalyzer_tester.hpp
│   │   │   ├── loader_tester.hpp
│   │   ├── drivers/             # Additional utility files
│   │   │   ├── manchester_encoder.c
│   │   │   ├── manchester_encoder.h
│   │   ├── analyzer.hpp         # Atomic model: Analyzer
│   │   ├── filter.hpp           # Atomic model: Filter
│   │   ├── filterAnalyzer.hpp   # Coupled model: Filter + Analyzer
│   │   ├── loader.hpp           # Atomic model: Loader
│   │   ├── top.hpp              # Coupled model: Top-level system
│   ├── test_runs/               # Main test files for execution
│   │   ├── main_analyzer_tester.cpp
│   │   ├── main_filter_tester.cpp
│   │   ├── main_filterAnalyzer_tester.cpp
│   │   ├── main_loader_tester.cpp
|   ├── CMakeLists.txt           # CMake configuration for the project
|   ├── idf_component.yml        # ESP-IDF component configuration file
│   ├── main.cpp                 # Main file to simulate the full system
├── test_files/                  # Input test cases for models
│   ├── analyzer/
│   │   ├── test1/
│   │   │   ├── analyzer_test.txt
│   │   ├── test2/
│   │   │   ├── analyzer_test.txt
│   ├── filter/
│   │   ├── test1/
│   │   │   ├── filter_input_test.txt
│   │   │   ├── filter_done_signal_test.txt
│   │   ├── test2/
│   │   │   ├── filter_input_test.txt
│   │   │   ├── filter_done_signal_test.txt
│   ├── filterAnalyzer/
│   │   ├── test1/
│   │   │   ├── filterAnalyzer_test.txt
│   │   ├── test2/
│   │   │   ├── filterAnalyzer_test.txt
├── .gitignore                    # Git ignore file
├── build_esp.sh                  # Build script for ESP32
├── build_sim.sh                  # Build script for Cadmium simulation
├── CMakeLists.txt                # CMake configuration for building the project
├── dependencies.lock             # Dependency management file
└── README.md                     # This documentation file
```

## System Components (Atomic Models)

This project consists of three main atomic components: **Loader**, **Filter**, and **Analyzer**. Each component plays a crucial role in the **Image Processing System**, ensuring images are processed sequentially from loading to filtering to analysis.

### **1. Loader**  
**File:** [loader.hpp](main/include/loader.hpp)  

The **Loader** initializes with a list of `.jpg` images, converts each image to `.png`, and sequentially sends one image every 5 seconds to the **Filter**. Once all images are sent, it deactivates.

---

### **2. Filter**  
**File:** [filter.hpp](main/include/filter.hpp)  

The **Filter** receives images from the **Loader**, processes them, and sends them to the **Analyzer**. It maintains an internal queue and processes images sequentially. It waits for a **"done"** signal from the **Analyzer** before processing the next image.

---

### **3. Analyzer**  
**File:** [analyzer.hpp](main/include/analyzer.hpp)  

The **Analyzer** receives filtered images, performs analysis, and generates an analysis report. After processing, it sends a **"done"** signal to the **Filter**, allowing it to process the next image.

## Coupled Models

This system integrates multiple atomic models into **coupled models**, which define the hierarchical structure and data flow of the image processing pipeline.

### **1. FilterAnalyzer System**  
**File:** [filterAnalyzer.hpp](main/include/filterAnalyzer.hpp)  

The **FilterAnalyzer** system combines the **Filter** and **Analyzer** models. It manages image processing and analysis while ensuring proper synchronization.

---

### **2. Top Model**  
**File:** [top.hpp](main/include/filterAnalyzer.hpptop.hpp)  

The **Top Model** is the highest-level coupled model, integrating the **Loader** and **FilterAnalyzer** to manage the full image processing pipeline.

## Test Models

This section provides test models for validating the behavior of individual components in the Image Processing System.

### **Loader Tester**
**File:** [loader_tester.hpp](main/include/devs_tests/loader_tester.hpp)

### **Description**  
The **Loader Tester** is a coupled model designed to test the **Loader** atomic model. It initializes the Loader with a list of images and ensures they are processed sequentially.

#### **Functionality**  
- Initializes the **Loader** with a predefined list of images.
- Outputs an image every 5 seconds.
- Confirms the Loader deactivates after processing all images.

---

### **Filter Tester**
**File:** [filter_tester.hpp](main/include/devs_tests/filter_tester.hpp)

#### **Description**  
The **Filter Tester** is a coupled model designed to validate the behavior of the **Filter** atomic model. It simulates receiving images from the **Loader** and handling "done" signals from the **Analyzer**.

#### **Functionality**  
- Uses input files to provide test images and "done" signals at specific times.
- Takes images as input and queues them for processing.
- Ouputs the filtered images.
- Waits for a "done" signal before processing the next image.

---

### **Analyzer Tester**
**File:** [analyzer_tester.hpp](./devs_tests/analyzer_tester.hpp)

#### **Description**  
The **Analyzer Tester** is a coupled model designed to validate the behavior of the **Analyzer** atomic model. It simulates receiving filtered images from the **Filter** and generating analysis reports.

#### **Functionality**  
- Uses an input file to provide test filtered images at specific times.
- Takes filtered images as input and processes them.
- Generates an analysis report for each image and outputs it.
- Sends a "done" signal after processing to indicate readiness for the next image.

---

### **FilterAnalyzer Tester**
**File:** [filterAnalyzer_tester.hpp](main/include/devs_tests/filterAnalyzer_tester.hpp)

#### **Description**  
The **FilterAnalyzer Tester** is a coupled model that validates the interaction between the **Filter** and **Analyzer** atomic models. It ensures that images flow correctly through the **FilterAnalyzer** system, from filtering to analysis.

#### **Functionality**  
- Uses an input file to provide test images at specific times.
- Sends images to the **Filter**, which processes and forwards them to the **Analyzer**.
- The **Analyzer** generates reports and sends "done" signals to allow the **Filter** to process the next image.
- Simulates the full pipeline from filtering to analysis.

## **Main Simulation Files**  

This section contains different main files used to execute and test the **Image Processing System**. Each file initializes the system components and runs simulations under various configurations.  

### **Loader Test**  
**File:** [main_loader_tester.cpp](main/test_runs/main_loader_tester.cpp)  

This test runs the **Loader** component to verify its behavior when processing images. The simulation logs will display the **image processing sequence** in the terminal.  

#### **Running Different Tests**

- Basic Image Loading Test (Test 1) → Set image_list = {"image1.jpeg", "image2.jpeg"}

- Empty List Test (Test 2) → Set image_list = {}

Modify the following line in `main_loader_tester.cpp` to switch between tests::  

```cpp
std::vector<std::string> image_list = {"image1.jpeg", "image2.jpeg"};
```

---

### **Filter Test**  
**File:** [main_filter_tester.cpp](main/test_runs/main_filter_tester.cpp)

This test runs the **Filter** component to validate its behavior when processing images and handling the "done" signal from the Analyzer.
When executed, the simulation logs will display the image filtering process in the terminal.  

#### **Setup Instructions**  
Before running the test, update the following lines in `filter_tester.hpp` to match your system's file path:

```cpp
std::string filter_input_test = "/absolute/path/to/devs-image-processing-system/test_files/filter/" + test + "/filter_input_test.txt";

std::string filter_done_signal_test = "/absolute/path/to/devs-image-processing-system/test_files/filter/" + test + "/filter_done_signal_test.txt"
```

#### **Running Different Tests**

- Basic Image Filtering Test (Test 1) → Set test = "test1"

- No "Done" Signal Test (Test 2) → Set test = "test2"

Modify the following line in `filter_tester.hpp` to switch between tests::  

```cpp
std::string test = "test1"
```

---

### **Analyzer Test**  
**File:** [main_analyzer_tester.cpp](main/test_runs/main_analyzer_tester.cpp)  

This test runs the **Analyzer** component to validate its ability to process filtered images and generate reports.  
When executed, the simulation logs will display the processing sequence and generated reports in the terminal.  

#### **Setup Instructions**  
Before running the test, update the following line in `analyzer_tester.hpp` to match your system's file path:

```cpp
std::string analyzer_test = "/home/sajaf/devs-image-processing-system/test_files/analyzer/" + test + "/analyzer_test.txt"
```

#### **Running Different Tests**  

- **Standard Image Analysis Test (Test 1)** → Set `test = "test1"`  
- **Simultaneous Image Input Test (Test 2)** → Set `test = "test2"`  

Modify the following line in `analyzer_tester.hpp` to switch between tests:  

```cpp
std::string test = "test1";
```

---

### **FilterAnalyzer Test**  
**File:** [main_filterAnalyzer_tester.cpp](main/test_runs/main_filterAnalyzer_tester.cpp)  

This test runs the **FilterAnalyzer** coupled model to validate the integration of the **Filter** and **Analyzer** components.  
When executed, the simulation logs will display the filtering and analysis process, including image processing and the generation of reports.

#### **Setup Instructions**  
Before running the test, update the following line in `filterAnalyzer_tester.hpp` to match your system's file path:

```cpp
std::string filter_input_test = "/absolute/path/to/devs-image-processing-system/test_files/filterAnalyzer/" + test + "/filterAnalyzer_test.txt";
```

#### **Running Different Tests**  

- **Sequential Image Processing Pipeline Test (Test 1)** → Set `test = "test1"`  
- **Simultaneous Image Processing Test (Test 2)** → Set `test = "test2"`  

Modify the following line in `filterAnalyzer_tester.hpp` to switch between tests:  

```cpp
std::string test = "test1";
```

---

### **Standard Simulation**  
**File:** [main.cpp](./main.cpp)  

This file initializes and runs the **Image Processing System** using Cadmium. It sets up the **Top Model**, which integrates the **Loader, Filter, and Analyzer**, processes a predefined list of images, and executes the simulation for **25 seconds** to complete the full workflow.  

## Dependencies
This project assumes that you have Cadmium installed in a location accessible by the environment variable $CADMIUM.
_This dependency would be met by default if you are using the DEVSsim servers. To check, try `echo $CADMIUM` in the terminal_

## Build
To build this project, run:
```sh
source build_sim.sh
```

__NOTE__: Everytime you run build_sim.sh, the contents of `build/` and `bin/` will be replaced.


## **Execute**  

To test each model, run the corresponding executable and check the logs in your terminal.  

### **Loader Test**  
To test the **Loader** model, run:  
```sh
./bin/Loader_Tester
```
This will execute the **Loader** model and display its behavior in the terminal logs.

### **Filter Test**  
To test the **Filter** model, run:  
```sh
./bin/Filter_Tester
```
This will execute the **Filter** model and log how it processes images and handles the "done" signal.

### **Analyzer Test**  
To test the **Analyzer** model, run:  
```sh
./bin/Analyzer_Tester
```
This will execute the **Analyzer** model and log how it generates reports and sends the "done" signal.

### **FilterAnalyzer Coupled Model Test**  
To test the **FilterAnalyzer** coupled model, run:  
```sh
./bin/FilterAnalyzer_Tester
```
This will execute the **FilterAnalyzer** system, combining Filter and Analyzer, and log the full filtering and analysis process.

### **Full System Execution**  
To test the entire **Image Processing System**, run:  
```sh
./bin/Image_Processing_System
```
This will simulate the complete image processing workflow, from loading images to generating analysis reports.