#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "axgl/namespace.h"
#include "axgl/render/mesh.h"

NAMESPACE_RENDER

class Model
{
public:
    glm::vec3 scale{ 1.0f };
    glm::vec3 rotation{ 0.0f };
    glm::vec3 translation{ 0.0f };

private:
    std::shared_ptr<Mesh> mesh_;

    glm::mat4 model_matrix_{ 1.0f };

public:
    void update_transform();
    void set_mesh(std::shared_ptr<Mesh> mesh);
    void render(const RenderContext& context);
};

NAMESPACE_RENDER_END
