cmake_minimum_required(VERSION 3.0.0)
project(bgfx-dev VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/_bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(_external/glm)
add_subdirectory(_external/glfw)
add_subdirectory(_external/spdlog)
add_subdirectory(_external/bgfx.cmake)

add_subdirectory(axgl)

add_subdirectory(bgfx-helloworld)
add_subdirectory(playground)
