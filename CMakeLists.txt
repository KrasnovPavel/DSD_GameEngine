cmake_minimum_required(VERSION 3.8)
project(DSD_GameEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}-${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}-${CMAKE_BUILD_TYPE})

add_subdirectory(DSD_Core)

add_executable(DSD_GameEngine ${SOURCE_FILES})
