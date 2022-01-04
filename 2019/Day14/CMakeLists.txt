cmake_minimum_required(VERSION 3.11.0)

set(TARGET_NAME day14_spaceStoichiometry)
project(${TARGET_NAME})

#Bring the headers, such as Student.h into the project
include_directories(include)
include_directories(".")
include_directories(../utils)

file(GLOB INCLUDES "include/*.h")
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDES})

install(TARGETS ${TARGET_NAME} DESTINATION deploy)