cmake_minimum_required(VERSION 3.0.0)
project(bgfx-dev VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/_bin)

add_subdirectory(_external/glfw)
add_subdirectory(_external/bgfx.cmake)

add_subdirectory(bgfx-helloworld)
add_subdirectory(playground)
