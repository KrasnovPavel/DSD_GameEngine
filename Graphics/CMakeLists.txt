cmake_minimum_required(VERSION 3.8)
project(Graphics)

set(SOURCE_FILES Mesh.h Mesh.cpp MeshParser.h MeshParser.cpp
        )


add_library(Graphics SHARED ${SOURCE_FILES})
set_target_properties(Graphics PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Graphics Core)
