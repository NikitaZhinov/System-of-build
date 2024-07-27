find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
	message("Doxygen build started")
	add_custom_target(doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM)
	message("Doxygen build finished")
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()
