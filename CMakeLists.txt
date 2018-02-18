cmake_minimum_required(VERSION 3.8)
project(DSD_GameEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

include_directories(./)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}-${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}-${CMAKE_BUILD_TYPE})

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(Logging)
add_subdirectory(Phisics)

add_executable(DSD_GameEngine ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(DSD_GameEngine Core Phisics Graphics ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
