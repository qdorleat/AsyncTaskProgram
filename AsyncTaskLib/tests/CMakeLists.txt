enable_testing()

# unit_StateMachineTest
add_executable(unit_StateMachineTest unit_StateMachineTest.cpp)
target_link_libraries(unit_StateMachineTest PUBLIC
        AsyncTaskLib
        GTest::gtest
)

add_test(NAME unit_StateMachineTest
        COMMAND unit_StateMachineTest
)

# unit_ASynchronousTask
add_executable(unit_ASynchronousTask unit_ASynchronousTask.cpp)
target_link_libraries(unit_ASynchronousTask PUBLIC
        AsyncTaskLib
        GTest::gtest
)

add_test(NAME unit_ASynchronousTask
        COMMAND unit_ASynchronousTask
)

# unit_ThreadPool
add_executable(unit_ThreadPool unit_ThreadPool.cpp)
target_link_libraries(unit_ThreadPool PUBLIC
        AsyncTaskLib
        GTest::gtest
)

add_test(NAME unit_ThreadPool
        COMMAND unit_ThreadPool
)