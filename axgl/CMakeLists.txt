
add_library(axgl)

target_sources(axgl
    PRIVATE
    ./src/window.cpp
    ./src/event_loop.cpp
    ./src/component/bgfx_window_component.cpp
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
