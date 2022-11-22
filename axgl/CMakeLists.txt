
add_library(axgl)

target_sources(axgl
    PRIVATE
    ./src/window.cpp

    ./src/render/mesh.cpp
    ./src/render/model.cpp
    ./src/render/camera.cpp
    ./src/render/shader_program.cpp
    
    ./src/event/event_loop.cpp
    ./src/event/component/glfw.cpp
    ./src/event/component/bgfx.cpp

    ./res/shader/fs_pc.sc
    ./res/shader/vs_pc.sc
)

target_include_directories(axgl
    PRIVATE
    bgfx/include
    bimg/include
    bx/include
    glfw/include
    spdlog/include

    PUBLIC
    ./include
)

target_link_libraries(axgl
    PRIVATE
    bgfx
    bimg
    bx
    glfw
    spdlog
)

include(${CMAKE_SOURCE_DIR}/_cmake/shader.cmake)
bgfx_dev_add_shader_dir(${CMAKE_CURRENT_SOURCE_DIR}/res/shader)
