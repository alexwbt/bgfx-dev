#include "axgl/render/model.h"

NAMESPACE_RENDER

void Model::set_mesh(std::shared_ptr<Mesh> mesh)
{
    mesh_ = std::move(mesh);
}

void Model::set_rotation(bx::Vec3 rotation)
{
    rotation_ = rotation;
}

void Model::set_translation(bx::Vec3 translation)
{
    translation_ = translation;
}

void Model::rotate(bx::Vec3 delta)
{
    rotation_ = bx::add(rotation_, delta);
}

void Model::translate(bx::Vec3 delta)
{
    translation_ = bx::add(translation_, delta);
}

void Model::render(const RenderContext& context)
{
    if (!mesh_)
        return;

    float translate_matrix[16];
    bx::mtxTranslate(
        translate_matrix,
        translation_.x,
        translation_.y,
        translation_.z
    );

    float rotate_matrix[16];
    bx::mtxRotateXYZ(
        rotate_matrix,
        rotation_.x,
        rotation_.y,
        rotation_.z
    );

    float transform_matrix[16];
    bx::mtxMul(transform_matrix, translate_matrix, rotate_matrix);

    bgfx::setTransform(transform_matrix);
    mesh_->render(context);
}

NAMESPACE_RENDER_END
