cmake_minimum_required(VERSION 3.16)

project(Weathered VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick Network)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appWeathered
    main.cpp

    ApiAccess.hpp

    AppController.h AppController.cpp

    Weather-Service/Weather.h Weather-Service/Weather.cpp
    Weather-Service/WeatherModel.h Weather-Service/WeatherModel.cpp
    Weather-Service/WeatherDayModel.h Weather-Service/WeatherDayModel.cpp
    Weather-Service/WeatherDay.h Weather-Service/WeatherDay.cpp

    Quote-Service/lmManager.h Quote-Service/lmManager.cpp
)

qt_add_qml_module(appWeathered
    URI Weathered
    VERSION 1.0
    QML_FILES
        Qml/Main.qml

        Qml/WeatherBox.qml
        Qml/WeatherDelegate.qml

        Qml/QuoteBox.qml

        Qml/ClothingBox.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWeathered PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWeathered
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWeathered
    PRIVATE Qt6::Quick Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appWeathered
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
