
add_executable(playground)

target_sources(playground
    PRIVATE
    ./src/main.cpp
)

target_include_directories(playground
    PRIVATE

    glfw/include
    bgfx/include
    axgl/include
    spdlog/include
)

target_link_libraries(playground
    PRIVATE
    glm
    glfw
    bgfx
    axgl
    spdlog
)
