### juce-qt-practice

For practicing juce, qml, and juce with qml. <br>

I planned to use C++20 modules, but Qt has no support for them and it's not coming anytime soon. Macros cannot escape modules and Qt depends on them too heavily. Some early projects may use them and there is a build section if your curious, but will be using traditional header/source now.

To build any qml projects change this to your Qt installation in the CMakeLists : `set(CMAKE_PREFIX_PATH"/home/jax/Qt/6.7.2/gcc_64")`

---

Tests/Audio - only juce <br>
Tests/GUI - only qml <br>
Tests/Apps - juce and qml <br>


Project Descriptions :

- Test/Audio/
	- ConsoleNoise : Most simple audio system, least juce audio classes as possible.
	- ConsoleNoiseClean : Improved simple audio system. Uses ScopedJuceInitialiser_GUI to instance the MessageManager, which also solved leaks of related objects. Other audio related objects (Player, Manager..) are no longer created in global scope.
	- ConsoleNoiseCleanHeader : same as above but header/source instead of modules.
	- ConsoleNoiseMultiThread : Failed experiment just here to show how terrible I am.
	
- Tests/GUI/
	- NotifierReceiver : Design pattern to trade data between two objects in one qml document.
- Tests/App/
  - App0 : Play noise along with a QML window. This is Audio/ConsoleNoiseClean with the additional QML. The frameworks do not communicate, but shows how to build the project with them together.
  - App0Header : App0 but using header/source instead of modules. Also not subclass juce audio classes anymore. This would be your good starting point for juce+qt.


---

### CMake C++20 Module Support

Since CMake 3.28. The compilation of any given source that `import` a module requires the binary module interface (BMI) of that module - meaning the compilation of modules must be done before
the sources that depend on them. This strict logic requires build-time resolution, that is implemented in CMake's built-in 'scanner', which will scan all sources for module dependancies by default.


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
