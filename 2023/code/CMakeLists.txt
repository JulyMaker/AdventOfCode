cmake_minimum_required(VERSION 3.11.0)

set(TARGET_NAME adventOfCode2023)
project(${TARGET_NAME})

include_directories(".")
include_directories(include)
include_directories(../include/auxi)
include_directories(../utils)
include_directories(../inputs)

file(GLOB INCLUDES "include/*.h" "include/auxi/*.h" "../utils/*.h")
file(GLOB SOURCES "src/*.cpp" "src/auxi/*.cpp" "../utils/*.cpp" "../inputs/accesoInput.py")

#Keep directories structure for Visual Studio
function(assign_source_group)
      foreach(_file IN ITEMS ${ARGN})
      # Get the directory of the source file
      get_filename_component(_parentDir "${_file}" DIRECTORY)

      # Remove common directory prefix to make the group
      string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" _group "${_parentDir}")

      # Make sure we are using windows slashes
      string(REPLACE "/" "\\" _group "${_group}")

      source_group("${_group}" FILES "${_file}")
  endforeach()
endfunction(assign_source_group)

assign_source_group(${SOURCES})
assign_source_group(${INCLUDES})

add_library(advOCode2023 ${SOURCES} ${INCLUDES})
add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDES})


install(TARGETS ${TARGET_NAME} DESTINATION deploy)