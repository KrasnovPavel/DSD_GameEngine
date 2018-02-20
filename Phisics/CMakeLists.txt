cmake_minimum_required(VERSION 3.8)
project(Phisics)

set(SOURCE_FILES Collision/CollisionVolume.h Collision/CollisionSphere.h Collision/CollisionBox.h Collision/AABB.h Collision/CollisionChecker.cpp Collision/CollisionChecker.h Collision/Manifold.h Collision/AABB.cpp Collision/CollisionVolume.cpp Collision/CollisionSphere.cpp Collision/CollisionBox.cpp Collision/Manifold.cpp)


add_library(Phisics SHARED ${SOURCE_FILES})
set_target_properties(Phisics PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Phisics Core)