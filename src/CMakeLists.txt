cmake_minimum_required(VERSION 2.6)

project(FSSCAN_MAIN)

include_directories($ {FSSCAN_MAIN_SOURCE_DIR})

set(FSSCAN_MAIN_SRCS BaseClass.cxx Helper.cxx Logger.cxx BaseNode.cxx File.cxx MainApp.cxx)

add_library(fsscan_main SHARED ${FSSCAN_MAIN_SRCS})
