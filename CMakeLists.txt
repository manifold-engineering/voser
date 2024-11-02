cmake_minimum_required(VERSION 3.16)

project(voser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required Qt components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

# Include directories
include_directories(include externals/qcustomplot)

# Project sources
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    externals/qcustomplot/qcustomplot.cpp  # QCustomPlot source file
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(voser
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/widgets/containerwidget.cpp src/widgets/frequencymanagerwidget.cpp src/widgets/plotwidget.cpp src/widgets/sourcesmanagerwidget.cpp
        include/widgets/containerwidget.h include/widgets/frequencymanagerwidget.h include/widgets/plotwidget.h include/widgets/solver.h include/widgets/sourcesmanagerwidget.h include/widgets/sourcestablemodel.h
        include/globalconfig.h include/mainwindow.h include/solution.h include/solver.h include/source.h
        include/sourcestablemodel.h
        externals/qcustomplot/qcustomplot.h
        src/solver.cpp src/sourcestablemodel.cpp
    )
else()
    if(ANDROID)
        add_library(voser SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(voser
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link libraries
target_link_libraries(voser PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.voser)
endif()
set_target_properties(voser PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS voser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(voser)
endif()

# Add resources.qrc file
qt_add_resources(VOSER_RESOURCES resources.qrc)

# Include resources in the target
target_sources(voser PRIVATE ${VOSER_RESOURCES})

# Add .rc file for Windows
if(WIN32)
    target_sources(voser PRIVATE app_icon.rc)
endif()
