cmake_minimum_required(VERSION 2.8.9)

set(TARGET_NAME adventOfCode2023_test)
project(${TARGET_NAME})

#Bring the headers, such as Student.h into the project
include_directories(include)
include_directories(../code/include)
include_directories(../utils)

file(GLOB INCLUDES "include/*.h")
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

################################
# GTest
################################
add_subdirectory(./gtest-1.8.1)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
################################
# Unit Tests
################################
# Add test cpp file
add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDES})

# Link test executable against gtest & gtest_main
target_link_libraries(${TARGET_NAME} gtest gtest_main)
target_link_libraries(${TARGET_NAME} advOCode2023)

add_test( ${TARGET_NAME} ${TARGET_NAME} )