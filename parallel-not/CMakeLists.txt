cmake_minimum_required(VERSION 3.2)
project(parallel)

################################################################################
# Executable
################################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ${MPI_COMPILE_FLAGS}")

set(SOURCE_FILES main.cpp)
add_executable(parallel ${SOURCE_FILES})
