cmake_minimum_required(VERSION 3.20)

set(TEST_NAME sob_test)

include(CTest)

find_package(GTest CONFIG REQUIRED)

set(SRC_TEST main.cpp test.cpp sob.cpp lexer.cpp parser.cpp)
set(SRC_SOB ../src/build.cpp ../src/error.cpp ../src/lexer.cpp ../src/parser.cpp ../src/sob.cpp)
add_executable(${TEST_NAME} ${SRC_TEST} ${SRC_SOB})
target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_include_directories(${TEST_NAME} PRIVATE ../include)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
