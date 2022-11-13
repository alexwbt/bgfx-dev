
add_executable(playground)

target_sources(playground
    PRIVATE
    ./src/main.cpp
    ./src/window.cpp
)

target_include_directories(playground
    PRIVATE
    bgfx/include
    bimg/include
    bx/include
    glfw/include

    ./src
)

target_link_libraries(playground
    PRIVATE
    bgfx
    bimg
    bx
    glfw
)
