cmake_minimum_required(VERSION 3.8)
project(DSD_Core)

set(SOURCE_FILES DSDObject.cpp DSDObject.h)

add_library(DSD_Core SHARED ${SOURCE_FILES})