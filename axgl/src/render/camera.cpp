#include "axgl/render/camera.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <bx/math.h>

#include "axgl/spdlog.h"

NAMESPACE_RENDER

Camera::Camera()
{
    update();
}

void Camera::use(const RenderContext& context)
{
    glm::mat4 projection_matrix = glm::perspective(
        glm::radians(fov),
        static_cast<float>(context.width) /
        static_cast<float>(context.height),
        0.1f, 100.0f
    );

    float projection_matrix_[16];
    bx::mtxProj(
        projection_matrix_,
        fov,
        static_cast<float>(context.width) /
        static_cast<float>(context.height),
        0.1f,
        100.0f,
        bgfx::getCaps()->homogeneousDepth
    );

    // glm::mat4(projection_matrix);

    SPDLOG_DEBUG("projection equal: {}", glm::make_mat4x4(projection_matrix_) == projection_matrix);

    bgfx::setViewTransform(
        context.view_id,
        glm::value_ptr(view_matrix_),
        projection_matrix_
    );
}

void Camera::update()
{
    auto yaw_radians = glm::radians(yaw);
    auto pitch_radians = glm::radians(pitch);
    auto cos_yaw_radians = glm::cos(yaw_radians);
    auto sin_yaw_radians = glm::sin(yaw_radians);
    auto cos_pitch_radians = glm::cos(pitch_radians);
    auto sin_pitch_radians = glm::sin(pitch_radians);
    front_ = glm::normalize(glm::vec3(
        cos_yaw_radians * cos_pitch_radians,
        sin_pitch_radians,
        sin_yaw_radians * cos_pitch_radians
    ));
    front_side_ = glm::normalize(glm::vec3(cos_yaw_radians, 0, sin_yaw_radians));
    right_ = glm::normalize(glm::cross(front_, glm::vec3(0, 1, 0)));
    up_ = glm::normalize(glm::cross(right_, front_));

    view_matrix_ = glm::lookAt(position, position + front_, up_);

    float view[16];
    bx::mtxLookAt(view, bx::Vec3(bx::init::Zero), bx::add(bx::Vec3(position.x, position.y, position.z), bx::Vec3(front_.x, front_.y, front_.z)));

    SPDLOG_DEBUG("view equal: {}", glm::make_mat4x4(view) == view_matrix_);
}

const glm::mat4 Camera::view_matrix()
{
    return view_matrix_;
}

NAMESPACE_RENDER_END
