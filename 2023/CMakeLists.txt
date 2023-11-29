cmake_minimum_required (VERSION 3.11.0)
project(adventOfCode2023)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS On)


set(CMAKE_INSTALL_PREFIX "../")

add_subdirectory( code )
add_subdirectory( gtest)

########
#Resource file
########
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/utils/paths.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/utils/paths.h"
)

list( APPEND GENERATED_FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/paths.h
)