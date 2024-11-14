#-- Initial Configuration
cmake_minimum_required(VERSION 3.30.3)  # Specify minimum CMake version
project(ConsoleNoiseCleanHeader VERSION 0.0.1)     # Define the project name and version
set(CMAKE_CXX_STANDARD 20) # Set C++ version

#-- Framework Paths
set(JUCE_DIR "../../../Libraries/JUCE" CACHE PATH "Path to JUCE") # Set path to JUCE repository

#-- Framework CMake Support
add_subdirectory(${JUCE_DIR} JUCE) # Add JUCE

#-- Targets and Modules
juce_add_console_app(Main)

#-- Include Directories
target_include_directories(Main PRIVATE
    ${JUCE_DIR}/modules/juce_audio_devices
    ${JUCE_DIR}/modules/juce_audio_basics
    ${JUCE_DIR}/modules/juce_core
    ${JUCE_DIR}/modules/juce_events
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

#-- Sourcing
file(GLOB SOURCES
        "Source/*"
)

target_sources(Main
        PUBLIC
        "Main.cpp"
        ${SOURCES}
)

#-- Macros
target_compile_definitions(Main
        PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
)

#-- Linking
target_link_libraries(Main
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_core
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)





