cmake_minimum_required(VERSION 3.5)

# Information from Kunai project
project(
    CFG
)

add_library(cfg-lib 
  STATIC
)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(lib)
add_subdirectory(tools)