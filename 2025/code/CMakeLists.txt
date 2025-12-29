cmake_minimum_required(VERSION 3.11.0)

set(TARGET_NAME adventOfCode2025)
project(${TARGET_NAME})

include_directories(include)
include_directories(../include/auxi)
include_directories(../utils)
include_directories(../inputs)

set(EIGEN_INCLUDE_DIR "../thirdParty/eigen-3.4.0")
include_directories(${EIGEN_INCLUDE_DIR})


set(GLPK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../thirdParty/glpk-5.0/src")
set(GLPK_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../thirdParty/glpk-5.0/w64/glpk.lib")

if(NOT EXISTS "${GLPK_INCLUDE_DIR}/glpk.h")
    message(FATAL_ERROR "glpk.h no encontrado en: ${GLPK_INCLUDE_DIR}")
endif()
if(NOT EXISTS "${GLPK_LIBRARY}")
    message(FATAL_ERROR "glpk.lib no encontrado en: ${GLPK_LIBRARY}")
endif()

add_library(glpk_lib STATIC IMPORTED)
set_target_properties(glpk_lib PROPERTIES
    IMPORTED_LOCATION "${GLPK_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${GLPK_INCLUDE_DIR}"
)

file(GLOB INCLUDES "include/*.h" "include/auxi/*.h" "../utils/*.h" "../utils/*.h.in")
file(GLOB SOURCES "src/*.cpp" "src/auxi/*.cpp" "../utils/*.cpp" "../inputs/accesoInput.py")


include(assign_source_group)
assign_source_group(${SOURCES})
assign_source_group(${INCLUDES})

add_library(advOCode2025 ${SOURCES} ${INCLUDES})
add_executable(${TARGET_NAME} ${SOURCES} ${INCLUDES})

target_link_libraries(adventOfCode2025 glpk_lib)
target_include_directories(adventOfCode2025 PRIVATE ${GLPK_INCLUDE_DIR})

install(TARGETS ${TARGET_NAME} DESTINATION deploy)