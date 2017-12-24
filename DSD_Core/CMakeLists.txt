cmake_minimum_required(VERSION 3.8)
project(DSD_Core)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES DSDBaseObject.h DSDBaseObject.cpp
    SerializationController.cpp SerializationController.h
    ReadByteArray.h ReadByteArray.cpp WriteByteArray.h WriteByteArray.cpp
    FileController.cpp FileController.h
    Vector3.h Vector3.cpp Vector4.h Vector4.cpp Quaternion.h Quaternion.cpp
    Triangle.h Triangle.cpp Mesh.h Mesh.cpp MeshParcer.cpp MeshParcer.h Exceptions.h MeshParcerSTL.cpp MeshParcerSTL.h)

add_subdirectory(Logging)

add_library(DSD_Core SHARED ${SOURCE_FILES})
set_target_properties(DSD_Core PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(DSD_Core Logging)
