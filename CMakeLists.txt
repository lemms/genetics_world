cmake_minimum_required (VERSION 2.8.12)
project (genetics_world CXX)
add_compile_options(-std=c++11)

set (genetics_world_VERSION_MAJOR 0)
set (genetics_world_VERSION_MINOR 1)

configure_file ("${PROJECT_SOURCE_DIR}/include/genetics_world.h.in" "${PROJECT_BINARY_DIR}/include/genetics_world.h") 

# Copy header files to build directory
file (GLOB include_files RELATIVE ${PROJECT_SOURCE_DIR} "${PROJECT_SOURCE_DIR}/include/*.h")
file (COPY ${include_files} DESTINATION "${PROJECT_BINARY_DIR}/include/")

include_directories ("${PROJECT_BINARY_DIR}/include")
add_subdirectory (src bin)
