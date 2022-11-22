#pragma once

#include <vector>
#include <memory>

#include "axgl/namespace.h"
#include "axgl/render/mesh.h"

#include <bx/math.h>

NAMESPACE_RENDER

class Model
{
private:
    std::shared_ptr<Mesh> mesh_ = nullptr;

    bx::Vec3 rotation_{ bx::init::Zero };
    bx::Vec3 translation_{ bx::init::Zero };

public:
    void set_mesh(std::shared_ptr<Mesh> mesh);

    void set_rotation(bx::Vec3 rotation);
    void set_translation(bx::Vec3 translation);

    void rotate(bx::Vec3 delta);
    void translate(bx::Vec3 delta);

    void render(const RenderContext& context);
};

NAMESPACE_RENDER_END
