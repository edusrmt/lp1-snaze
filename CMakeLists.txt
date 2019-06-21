cmake_minimum_required(VERSION 3.5)
project (Snaze VERSION 1.0.0 LANGUAGES CXX )

#=== FINDING PACKAGES ===#

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#Include dir
include_directories( include )

#=== Main App ===
file(GLOB SOURCES "src/*.cpp")

set(EXECUTABLE_OUTPUT_PATH "bin")
add_executable(snaze ${SOURCES})