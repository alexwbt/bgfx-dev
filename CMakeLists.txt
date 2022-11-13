cmake_minimum_required(VERSION 3.0.0)
project(bgfx-dev VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/_bin)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("_external/bgfx.cmake")

add_executable(bgfx-dev main.cpp)
target_link_libraries(bgfx-dev bgfx)
