cmake_minimum_required(VERSION 3.8)
project(DSD_GameEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}-${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}-${CMAKE_BUILD_TYPE})

add_subdirectory(DSD_Core)

add_executable(DSD_GameEngine ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(DSD_GameEngine DSD_Core ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
