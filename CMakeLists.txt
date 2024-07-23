cmake_minimum_required(VERSION 3.20)
project(sob)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(${PROJECT_NAME} "src/main.cpp" "src/sob.cpp" "src/lexer.cpp" "src/parser.cpp" "src/build.cpp" "src/error.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE "include")
