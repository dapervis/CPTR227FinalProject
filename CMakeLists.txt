cmake_minimum_required(VERSION 3.0.0)
project(aardvark VERSION 0.3.0)

set(PROJECT_SOURCE_DIR "src")
set(DOXYGEN_OUPUT_DIR "doxygen")
set(DOXYGEN_HTML_OUPUT_DIR "../docs")
set(DOXYGEN_IN_FILE "Doxyfile.in")
# Be sure to change the executable name, 
# and change the input file name if it is different.
add_executable(doxygenTry1 ${PROJECT_SOURCE_DIR}/main.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Doxygen

# look for Doxygen package
find_package(Doxygen)

if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYGEN_OUPUT_DIR}/${DOXYGEN_IN_FILE})
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target( docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )

    add_custom_target( pdf
        COMMAND make
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYGEN_OUPUT_DIR}/latex/refman.pdf ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYGEN_OUPUT_DIR}/${DOXYGEN_HTML_OUPUT_DIR}/${PROJECT_NAME}.pdf
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYGEN_OUPUT_DIR}/latex
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYGEN_OUPUT_DIR}/latex/refman.tex
        COMMENT "Generating PDF from LaTex"
    )

else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
