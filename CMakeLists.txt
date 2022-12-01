cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME AsyncTaskProgram)

project(${PROJECT_NAME}
        LANGUAGES CXX
        VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Concurrent)

set(_sources
    CommandParser.cpp
    sources/ASynchronousTask.cpp
    sources/ThreadPool.cpp
)

set(_headers
    CommandParser.h
    CommandType.h
    sources/ASynchronousTask.h
    sources/ThreadPool.h
)

set(_resources
    resources/jobs/jobs.qrc
)

add_executable(AsyncTaskProgram
    main.cpp
    ${_sources}
    ${_headers}
    ${_resources}
)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${ARG_INCLUDE_DIR}>"	# For build-tree
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>	# For install-tree
)

target_link_libraries(AsyncTaskProgram PUBLIC
    Qt5::Core
    Qt5::Concurrent
    Qt5::Gui
    Qt5::Widgets
)
