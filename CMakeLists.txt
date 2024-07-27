cmake_minimum_required(VERSION 3.20)
project(sob)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
	set(CMAKE_CXX_FLAGS_RELEASE "/O2")
endif()

set(SRC_SOB src/build.cpp src/error.cpp src/lexer.cpp src/parser.cpp src/sob.cpp)
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_SOB})
target_include_directories(${PROJECT_NAME} PRIVATE include)

find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
	message("Doxygen build started")
	add_custom_target(doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM)
	message("Doxygen build finished")
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()

include(CTest)

find_package(GTest CONFIG REQUIRED)

set(TEST_NAME sob_test)
set(SRC_TEST test/main.cpp test/test.cpp test/sob.cpp test/lexer.cpp test/parser.cpp)
add_executable(${TEST_NAME} ${SRC_TEST} ${SRC_SOB})
target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_include_directories(${TEST_NAME} PRIVATE include)
	
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
