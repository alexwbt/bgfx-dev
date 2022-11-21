#include "axgl/render/camera.h"

NAMESPACE_RENDER

Camera::Camera()
{
    update();
}

void Camera::use(const RenderContext& context)
{
    float projection_matrix[16];
    bx::mtxProj(
        projection_matrix,
        fov,
        float(context.width) / float(context.height),
        0.1f,
        100.0f,
        bgfx::getCaps()->homogeneousDepth
    );

    bgfx::setViewTransform(context.view_id, view_matrix_, projection_matrix);
}

void Camera::update()
{
    auto yaw_radians = bx::toRad(yaw);
    auto pitch_radians = bx::toRad(pitch);
    auto cos_yaw_radians = bx::cos(yaw_radians);
    auto sin_yaw_radians = bx::sin(yaw_radians);
    auto cos_pitch_radians = bx::cos(pitch_radians);
    auto sin_pitch_radians = bx::sin(pitch_radians);
    front_ = bx::normalize(bx::Vec3(
        cos_yaw_radians * cos_pitch_radians,
        sin_pitch_radians,
        sin_yaw_radians * cos_pitch_radians
    ));
    front_side_ = bx::normalize(bx::Vec3(cos_yaw_radians, 0, sin_yaw_radians));
    right_ = bx::normalize(bx::cross(front_, bx::Vec3(0, 1, 0)));
    up_ = bx::normalize(bx::cross(right_, front_));

    bx::mtxLookAt(view_matrix_, position, bx::add(position, front_));
}

const float* Camera::view_matrix()
{
    return view_matrix_;
}

NAMESPACE_RENDER_END
