
add_library(axgl)


file(GLOB_RECURSE source_cpp_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
file(GLOB_RECURSE shader_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "res/shader/*.sc")

target_sources(axgl
    PRIVATE
    ${source_cpp_files}
    ${shader_files}
)

target_include_directories(axgl
    PRIVATE

    bx/include
    glfw/include
    bimg/include
    bgfx/include
    spdlog/include

    PUBLIC
    ./include
)

target_link_libraries(axgl
    PRIVATE
    bx
    glm
    glfw
    bimg
    bgfx
    spdlog
)

include(${CMAKE_SOURCE_DIR}/_cmake/shader.cmake)
bgfx_dev_add_shader_dir(${CMAKE_CURRENT_SOURCE_DIR}/res/shader)
