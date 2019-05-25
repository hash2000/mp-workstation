cmake_minimum_required(VERSION 3.0.0)
project(Navigator)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
) 

add_executable(Navigator ${PROJECT_SOURCE_DIR}/src/Navigator.cpp)

set(QUICK_START_VERSION_MAJOR 1)
set(QUICK_START_VERSION_MINOR 0)

file(GLOB
  SOURCE_FILES
    *.cpp
    ${PROJECT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

