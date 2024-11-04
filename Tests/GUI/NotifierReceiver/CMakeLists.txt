cmake_minimum_required(VERSION 3.16)
project(Null VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/home/jax/Qt/6.7.2/gcc_64")

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(Exe
    Main.cpp
)

qt_add_qml_module(moduleMain
    URI Main
    VERSION 1.0
    QML_FILES
        Main.qml
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Main
)

qt_add_qml_module(moduleNotifRec
    URI NotifRec
    VERSION 1.0
    QML_FILES
        Notif.qml
        Receiver.qml
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/NotifRec
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(Exe PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Exe
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(Exe
    PRIVATE 
    Qt6::Quick
    moduleMain
    moduleNotifRec
)

include(GNUInstallDirs)
install(TARGETS Exe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
