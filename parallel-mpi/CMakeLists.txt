cmake_minimum_required(VERSION 3.2)
project(parallel)

################################################################################
# MPI
################################################################################
find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})
link_directories(${MPI_LINK_PATH})

if (NOT ${MPI_FOUND})
    message(FATAL_ERROR "LLVM libraries not found")
endif ()

################################################################################
# Executable
################################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ${MPI_COMPILE_FLAGS}")

set(SOURCE_FILES main.cpp)
add_executable(parallel ${SOURCE_FILES})

target_link_libraries(parallel ${MPI_LIBRARIES})