#-- Initial Configuration

cmake_minimum_required(VERSION 3.30.3)  # specify minimum CMake version
project(ConsoleNoise VERSION 0.0.1)     # define the project name and version
set(CMAKE_CXX_STANDARD 20) # set C++ version

#-- Framework Paths

set(CMAKE_PREFIX_PATH "/home/jax/Qt/6.7.2/gcc_64") # Qt installation path
set(JUCE_DIR "../../../Libraries/JUCE" CACHE PATH "Path to JUCE") # JUCE repository path

#-- Framework Support

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick) # add Qt
qt_standard_project_setup(REQUIRES 6.5) # Qt config
add_subdirectory(${JUCE_DIR} JUCE) # add JUCE

#-- Targets and Modules

qt_add_executable(Exe
        Main.cpp
)

qt_add_qml_module(moduleMain
        URI Main
        VERSION 1.0
        QML_FILES
        Main.qml
        OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/moduleMain
)

#-- Include Directories

target_include_directories(Exe PRIVATE
    ${JUCE_DIR}/modules/juce_audio_devices
    ${JUCE_DIR}/modules/juce_audio_basics
    ${JUCE_DIR}/modules/juce_core
    ${JUCE_DIR}/modules/juce_events
)

#-- Additional Target / Source Configuration

target_compile_definitions(Exe
        PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
)

set_property(SOURCE "Main.cpp" PROPERTY CXX_SCAN_FOR_MODULES ON)

#-- Linking

target_link_libraries(Exe
        PRIVATE
        Qt6::Quick
        moduleMain
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_core
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)


#-- Sources

file(GLOB SOURCES
        "Source/*.ixx"
)

target_sources(Exe
        PUBLIC
        FILE_SET CXX_MODULES
        FILES ${SOURCES}
)

