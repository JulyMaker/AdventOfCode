cmake_minimum_required(VERSION 3.11.0)

set(TARGET_NAME adventOfCode2023)
project(${TARGET_NAME})

#Bring the headers, such as Student.h into the project
include_directories(include)
include_directories(".")
include_directories(../utils)
include_directories(../inputs)

file(GLOB INCLUDES "include/*.h")
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp" "*.cpp" "../utils/*.cpp" "../inputs/accesoInput.py")

add_library(advOCode2023 ${SOURCES} ${INCLUDES})
add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDES})
target_link_libraries(${TARGET_NAME} advOCode2023)

install(TARGETS ${TARGET_NAME} DESTINATION deploy)