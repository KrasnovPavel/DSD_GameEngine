cmake_minimum_required(VERSION 3.8)
project(Phisics)

set(SOURCE_FILES ColisionVolumes/CollisionVolume.h ColisionVolumes/CollisionSphere.h ColisionVolumes/CollisionBox.h ColisionVolumes/AABB.h)


add_library(Phisics SHARED ${SOURCE_FILES})
set_target_properties(Phisics PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Phisics Core)