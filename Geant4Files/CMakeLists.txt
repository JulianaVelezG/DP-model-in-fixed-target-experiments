cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(2025Project)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

file(GLOB MACRO_FILES "macros/*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${CMAKE_BINARY_DIR}/)

add_executable(project project.cc ${sources} ${headers})
target_link_libraries(project ${Geant4_LIBRARIES})
add_custom_target(2025Project DEPENDS project)
