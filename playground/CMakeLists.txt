
add_executable(playground)

target_sources(playground
    PRIVATE
    ./src/main.cpp
)

target_include_directories(playground
    PRIVATE
    axgl/include

    glfw/include
    bgfx/include
    bimg/include
    bx/include

    ./src
)

target_link_libraries(playground
    PRIVATE
    axgl

    glfw
    bgfx
    bimg
    bx
)
