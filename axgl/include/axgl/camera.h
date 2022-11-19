#pragma once

#include <bx/math.h>

namespace gl
{
    class Camera
    {
    public:
        bx::Vec3 position = { 0.0f, 0.0f, 0.0f };
        bx::Vec3 direction = { 0.0f, 0.0f, 0.0f };
    };
}
