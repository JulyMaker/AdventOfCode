cmake_minimum_required(VERSION 3.11.0)

set(TARGET_NAME adventOfCode2023_test)
project(${TARGET_NAME})


include_directories(include)
include_directories(../utils)
include_directories(../code/include)

file(GLOB INCLUDES "include/*.h")
file(GLOB SOURCES "src/*.cpp")

################################
# GTest
################################
set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)

add_subdirectory(./googletest-1.14.0)
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