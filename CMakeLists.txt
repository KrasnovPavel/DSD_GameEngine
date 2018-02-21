cmake_minimum_required(VERSION 3.8)
project(DSD_GameEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

include_directories(./)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}-${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/../${CMAKE_PROJECT_NAME}-${CMAKE_BUILD_TYPE})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(Logging)
add_subdirectory(Phisics)

add_executable(DSD_GameEngine ${SOURCE_FILES})
target_link_libraries(DSD_GameEngine Logging Core Phisics Graphics ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# Start of Google test settings #
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES ${CMAKE_BINARY_DIR}/googletest-src/googletest/src/gtest_main.cc Tests/TestsMath.cpp)
add_executable(DSD_Test ${TEST_SOURCE_FILES})
target_link_libraries(DSD_Test Core Phisics Graphics ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} gtest)
