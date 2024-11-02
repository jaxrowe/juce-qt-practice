### juce-qt-practice

For practicing juce, qml, and juce with qml. <br>
C++20 modules will try to be used, CMake 3.30 and clang++ 18.1.3 supports them.

---

Tests/Audio - only juce <br>
Tests/GUI - only qml <br>
Tests/Apps - juce and qml <br>


Project Descriptions :

- Test/Audio/
	- ConsoleNoise : most simple audio system, least juce audio classes as possible.
	- ConsoleNoiseMultiThread : failed experiment just here to show how terrible I am

---

### CMake C++20 Module Support

Since CMake 3.28. The compilation of any given source that `import` a module requires the binary module interface (BMI) of that module - meaning the compilation of modules must be done before
the sources that depend on them. This strict logic requires build-time resolution, that is implemented in CMake's built-in 'scanner', which will scan all sources for module dependancies by default.

---

Modules must be added to the targets `CXX_MODULES` file set :
```
target_sources(Target
    PUBLIC
        FILE_SET CXX_MODULES
        FILES Module.ixx
)
```

Alternately, to a libraries `CXX_MODULES` which is target linked :

```
add_library(Module STATIC)
add_executable(Target Main.cpp)

target_sources(Module
    PUBLIC
        FILE_SET CXX_MODULES
        FILES testModule.ixx
)

target_link_libraries(Target PRIVATE Module)
```

All sources should be scanned for module dependencies by default, given the _Scanning Control_ section of the first link in **Resource** footer. But it's found to not be true, at least for entry points (that are not added to CXX_MODULES file set). So you have to manually enable module scanning for everything that wouldn't be added in the file set and thus recognized that way.
<br>

To enable scanning globally, `set(CMAKE_CXX_SCAN_FOR_MODULES ON)` at the top (or at least before target creation), and this will set the property on all targets as they are created.
<br>

To enable scanning per target, `set_target_properties(Target PROPERTIES CXX_SCAN_FOR_MODULES ON)`
<br>

To enable scanning per source, `set_property(SOURCE "Source/Main.cpp" PROPERTY CXX_SCAN_FOR_MODULES ON)`, which may be the most efficient way for entry points.

---

#### Resource

- https://cmake.org/cmake/help/latest/manual/cmake-cxxmodules.7.html <br>
- https://www.kitware.com/import-cmake-the-experiment-is-over/ <br>
- https://cmake.org/cmake/help/latest/command/target_sources.html
