
add_library(axgl)

target_sources(axgl
    PRIVATE
    ./src/core.cpp
    ./src/window.cpp

    ./src/model/shader_program.cpp

    ./src/component/glfw.cpp
    ./src/component/bgfx.cpp
)

target_include_directories(axgl
    PRIVATE
    bgfx/include
    bimg/include
    bx/include
    glfw/include

    PUBLIC
    ./include
)

target_link_libraries(axgl
    PRIVATE
    bgfx
    bimg
    bx
    glfw
)
