cmake_minimum_required(VERSION 3.8)
project(Logging)

set(SOURCE_FILES DSDLogger.cpp DSDLogger.h)


add_library(Logging SHARED ${SOURCE_FILES})