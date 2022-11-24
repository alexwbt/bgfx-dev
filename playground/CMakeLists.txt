
add_executable(playground)

target_sources(playground
    PRIVATE
    ./src/main.cpp
)

target_include_directories(playground
    PRIVATE

    bx/include
    glfw/include
    bimg/include
    bgfx/include
    axgl/include
    spdlog/include
)

target_link_libraries(playground
    PRIVATE
    bx
    glm
    glfw
    bimg
    bgfx
    axgl
    spdlog
)

include(${CMAKE_SOURCE_DIR}/_cmake/texture.cmake)
bgfx_dev_add_texture_dir(${CMAKE_CURRENT_SOURCE_DIR}/res/texture)
