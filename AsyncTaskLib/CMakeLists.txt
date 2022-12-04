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
    include/ASynchronousTaskAlgoA.h
    include/ASynchronousTaskAlgoB.h
    include/Definitions.h
    include/TaskState.h
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

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)