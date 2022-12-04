enable_testing()

# unit_CommandParser
add_executable(unit_CommandParser unit_CommandParser.cpp)
target_link_libraries(unit_CommandParser PUBLIC
        AsyncTaskLib
        GTest::gtest
)

add_test(NAME unit_CommandParser
        COMMAND unit_CommandParser
)