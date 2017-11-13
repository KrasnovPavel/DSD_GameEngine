cmake_minimum_required(VERSION 3.8)
project(DSD_Core)

set(SOURCE_FILES DSDBaseObject.h SerializationController.cpp SerializationController.h ReadByteArray.h WriteByteArray.h WriteByteArray.cpp ReadByteArray.cpp FileController.cpp FileController.h)

add_subdirectory(Logging)

add_library(DSD_Core SHARED ${SOURCE_FILES})
set_target_properties(DSD_Core PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(DSD_Core Logging)