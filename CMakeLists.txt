cmake_minimum_required(VERSION 2.6)

project(FSSCAN)

SET(EXECUTABLE_OUTPUT_PATH ./bin)
SET(LIBRARY_OUTPUT_PATH ./bin)

option(BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON)
option(BUILD_TESTING "Set to ON to build testing" OFF)

include_directories($ {FSSCAN_SOURCE_DIR})

add_definitions("-Wall -ansi -pedantic")

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(testing)
  endif(BUILD_TESTING)

  add_executable(fs-scan src/main.cxx)

  target_link_libraries(fs-scan fsscan_main)