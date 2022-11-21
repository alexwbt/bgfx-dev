
add_executable(playground)

target_sources(playground
    PRIVATE
    ./src/main.cpp
)

target_include_directories(playground
    PRIVATE
    axgl/include

    bx/include
    bgfx/include
    bimg/include
    glfw/include
    spdlog/include

    ./src
)

target_link_libraries(playground
    PRIVATE
    axgl

    bx
    bgfx
    bimg
    glfw
    spdlog
)
