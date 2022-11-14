
add_executable(playground)

target_sources(playground
    PRIVATE
    ./src/main.cpp
)

target_include_directories(playground
    PRIVATE
    axgl/include

    ./src
)

target_link_libraries(playground
    PRIVATE
    axgl
)
