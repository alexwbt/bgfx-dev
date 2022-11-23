#pragma once

#include <glm/glm.hpp>

#include "axgl/namespace.h"
#include "axgl/render/render_context.h"

NAMESPACE_RENDER

class Camera
{
public:
    float yaw = 0.0f;
    float pitch = 0.0f;
    float fov = 80.0f;
    glm::vec3 position{ 0.0f };
    float near_clip = 0.1f;
    float far_clip = 100.0f;

private:
    glm::vec3 front_{ 0.0f };
    glm::vec3 front_side_{ 0.0f };
    glm::vec3 right_{ 0.0f };
    glm::vec3 up_{ 0.0f };

    glm::mat4 view_matrix_{ 0.0f };

public:
    Camera();
    virtual ~Camera() {}

    void use(const RenderContext& context);

    void update_transform();
    const glm::mat4 view_matrix();
};

NAMESPACE_RENDER_END
