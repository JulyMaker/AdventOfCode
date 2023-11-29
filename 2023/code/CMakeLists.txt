cmake_minimum_required(VERSION 3.11.0)

set(TARGET_NAME adventOfCode2023)
project(${TARGET_NAME})

include_directories(include)
include_directories(../include/auxi)
include_directories(../utils)
include_directories(../inputs)

file(GLOB INCLUDES "include/*.h" "include/auxi/*.h" "../utils/*.h" "../utils/*.h.in")
file(GLOB SOURCES "src/*.cpp" "src/auxi/*.cpp" "../utils/*.cpp" "../inputs/accesoInput.py")


include(assign_source_group)
assign_source_group(${SOURCES})
assign_source_group(${INCLUDES})

add_library(advOCode2023 ${SOURCES} ${INCLUDES})
add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDES})


install(TARGETS ${TARGET_NAME} DESTINATION deploy)