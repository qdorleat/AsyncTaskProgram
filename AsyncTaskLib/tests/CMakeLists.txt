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