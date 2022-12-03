cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME AsyncTaskProgram)

project(${PROJECT_NAME}
        LANGUAGES CXX
        VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Concurrent)

add_subdirectory(AsyncTaskLib)

set(_sources
    sources/CommandParser.cpp
)

set(_headers
    sources/CommandParser.h
    sources/CommandType.h
)

add_executable(AsyncTaskProgram
    main.cpp
    ${_sources}
    ${_headers}
)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${ARG_INCLUDE_DIR}>"	# For build-tree
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>	# For install-tree
        AsyncTaskLib/include
)

target_link_libraries(AsyncTaskProgram PUBLIC
    Qt5::Core
    Qt5::Concurrent
    Qt5::Gui
    Qt5::Widgets
    AsyncTaskLib
)
