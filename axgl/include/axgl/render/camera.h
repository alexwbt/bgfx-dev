#pragma once

#include <bx/math.h>

#include "axgl/namespace.h"
#include "axgl/render/render_context.h"

NAMESPACE_RENDER

class Camera
{
public:
    float yaw = 0.0f;
    float pitch = 0.0f;
    float fov = 80.0f;
    bx::Vec3 position{ bx::init::Zero };

private:
    bx::Vec3 front_{ bx::init::Zero };
    bx::Vec3 front_side_{ bx::init::Zero };
    bx::Vec3 right_{ bx::init::Zero };
    bx::Vec3 up_{ bx::init::Zero };

    float view_matrix_[16];

public:
    Camera();
    virtual ~Camera() {}

    void use(const RenderContext& context);

    void update();
    const float* view_matrix();
};

NAMESPACE_RENDER_END
