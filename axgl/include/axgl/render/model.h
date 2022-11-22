#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "axgl/namespace.h"
#include "axgl/render/mesh.h"

NAMESPACE_RENDER

class Model
{
private:
    std::shared_ptr<Mesh> mesh_ = nullptr;

public:
    glm::vec3 scale{ 1.0f };
    glm::vec3 rotation{ 0 };
    glm::vec3 translation{ 0 };

public:
    void set_mesh(std::shared_ptr<Mesh> mesh);
    void render(const RenderContext& context);
};

NAMESPACE_RENDER_END
