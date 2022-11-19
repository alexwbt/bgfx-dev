#pragma once

#include <axgl/model/shader/pc.h>

static std::vector<gl::shader::PC::Vertex> cube_vertices =
{
    {  0.5f,  0.5f, 0.0f, 0xff0000ff },
    {  0.5f, -0.5f, 0.0f, 0xff0000ff },
    { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
    { -0.5f,  0.5f, 0.0f, 0xff00ff00 }
};

static const std::vector<uint16_t> cube_indices =
{
    0,1,3,
    1,2,3
};
