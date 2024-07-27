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

add_executable(${PROJECT_NAME} "src/main.cpp" "src/sob.cpp" "src/lexer.cpp" "src/parser.cpp" "src/build.cpp" "src/error.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE "include")

add_subdirectory(doc)
add_subdirectory(test)
