
add_executable(bgfx-helloworld)

target_sources(bgfx-helloworld
    PRIVATE
    ./src/main.cpp
)

target_include_directories(bgfx-helloworld
    PRIVATE
    bgfx/include
    bimg/include
    bx/include
    glfw/include
)

target_link_libraries(bgfx-helloworld
    PRIVATE
    bgfx
    bimg
    bx
    glfw
)
