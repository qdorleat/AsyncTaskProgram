cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME AsyncTaskLib)

project(${PROJECT_NAME}
        LANGUAGES CXX
        VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

find_package(Qt5 REQUIRED COMPONENTS Concurrent Core)

set(_sources
    sources/ASynchronousTask.cpp
    sources/TaskStateMachine.cpp
    sources/ThreadPool.cpp
)

set(_headers
    include/ASynchronousTask.h
    include/TaskStateMachine.h
    include/ThreadPool.h
)

add_library(${PROJECT_NAME}
    ${_sources}
    ${_headers}
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Concurrent
    Qt5::Core
)
