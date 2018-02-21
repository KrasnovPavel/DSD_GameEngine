cmake_minimum_required(VERSION 3.8)
project(Core)

set(SOURCE_FILES DSDBaseObject.h DSDBaseObject.cpp
        Serialization/SerializationController.cpp Serialization/SerializationController.h
        Serialization/ReadByteArray.h Serialization/ReadByteArray.cpp Serialization/WriteByteArray.h Serialization/WriteByteArray.cpp
        Serialization/FileController.cpp Serialization/FileController.h
        Math/Vector3.h Math/Vector3.cpp Math/Vector4.h Math/Vector4.cpp Math/Quaternion.h Math/Quaternion.cpp
        Exceptions.h Math/GTestAlmostEqual.h Math/Functions.h)

add_library(Core SHARED ${SOURCE_FILES})
set_target_properties(Core PROPERTIES LINKER_LANGUAGE CXX)
