cmake_minimum_required(VERSION 3.8)
project(Logging)

set(SOURCE_FILES Logger.cpp Logger.h LoggerOutput.h)

add_library(Logging SHARED ${SOURCE_FILES})
target_link_libraries(Logging pthread)