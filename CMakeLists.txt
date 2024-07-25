cmake_minimum_required(VERSION 3.20)
project(sob)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(${PROJECT_NAME} "src/main.cpp" "src/sob.cpp" "src/lexer.cpp" "src/parser.cpp" "src/build.cpp" "src/error.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE "include")

find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
	message("Doxygen build started")
	add_custom_target(doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM )
else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)
