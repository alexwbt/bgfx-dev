
add_library(axgl)

target_sources(axgl
    PRIVATE
    ./src/core.cpp
    ./src/window.cpp

    ./src/model/mesh.cpp
    ./src/model/shader_program.cpp

    ./src/component/glfw.cpp
    ./src/component/bgfx.cpp

    ./res/shader/fs_pc.sc ./res/shader/vs_pc.sc
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

include(${CMAKE_SOURCE_DIR}/_cmake/shader.cmake)

bgfx_dev_add_shader(fs_pc.sc ${CMAKE_CURRENT_SOURCE_DIR}/res/shader)
bgfx_dev_add_shader(vs_pc.sc ${CMAKE_CURRENT_SOURCE_DIR}/res/shader)

source_group( "Shader Files" FILES ./res/shader/fs_pc.sc ./res/shader/vs_pc.sc)
