cmake_minimum_required(VERSION 3.8)
project(Graphics)

set(SOURCE_FILES Triangle.h Triangle.cpp Mesh.h Mesh.cpp Parsers/MeshParser.h Parsers/MeshParser.cpp
        Parsers/MeshParserSTL.cpp Parsers/MeshParserSTL.h)


add_library(Graphics SHARED ${SOURCE_FILES})
set_target_properties(Graphics PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Graphics Core)
