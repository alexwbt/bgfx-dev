#include "axgl/render/camera.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

NAMESPACE_RENDER

Camera::Camera()
{
    update_transform();
}

void Camera::use(const RenderContext& context)
{
    glm::mat4 projection_matrix = glm::perspective(
        glm::radians(fov),
        static_cast<float>(context.width) /
        static_cast<float>(context.height),
        near_clip, far_clip
    );

    bgfx::setViewTransform(
        context.view_id,
        glm::value_ptr(view_matrix_),
        glm::value_ptr(projection_matrix)
    );
}

void Camera::update_transform()
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

    // SPDLOG_DEBUG("view equal: {}", glm::make_mat4x4(view) == view_matrix_);
}

const glm::mat4 Camera::view_matrix()
{
    return view_matrix_;
}

NAMESPACE_RENDER_END
