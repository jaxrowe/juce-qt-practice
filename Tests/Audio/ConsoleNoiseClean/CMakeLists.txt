cmake_minimum_required(VERSION 3.30.3)  # specify minimum CMake version
project(ConsoleNoise VERSION 0.0.1)     # define the project name and version

set(CMAKE_CXX_STANDARD 20) # set C++ version
set(JUCE_DIR "../../../Libraries/JUCE" CACHE PATH "Path to JUCE") # set path to JUCE repository

add_subdirectory(${JUCE_DIR} JUCE) # add JUCE

#--

juce_add_console_app(Main)

target_include_directories(Main PRIVATE
    ${JUCE_DIR}/modules/juce_audio_devices
    ${JUCE_DIR}/modules/juce_audio_basics
    ${JUCE_DIR}/modules/juce_core
    ${JUCE_DIR}/modules/juce_events
)

target_compile_definitions(Main
        PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
)

target_sources(Main
        PUBLIC
        "Main.cpp")

set_property(SOURCE "Main.cpp" PROPERTY CXX_SCAN_FOR_MODULES ON)

target_link_libraries(Main
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_core
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)


file(GLOB SOURCES
        "Source/*.ixx"
)

target_sources(Main
        PUBLIC
        FILE_SET CXX_MODULES
        FILES ${SOURCES}
)

