#include "axgl/render/model.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "axgl/spdlog.h"

NAMESPACE_RENDER

void Model::update_transform()
{
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 rotation_matrix = glm::toMat4(glm::quat(rotation));
    glm::mat4 scale_matrix = glm::scale(scale);

    model_matrix_ = translation_matrix * rotation_matrix * scale_matrix;
}

void Model::set_mesh(std::shared_ptr<Mesh> mesh)
{
    mesh_ = std::move(mesh);
}

void Model::add_texture(std::shared_ptr<const Texture> texture)
{
    uint32_t max = bgfx::getCaps()->limits.maxTextureSamplers;
    if (textures_.size() < max)
        textures_.push_back(std::move(texture));
    else
        SPDLOG_ERROR(
            "Failed to add texture \"{}\", max texture count per model is {}.",
            texture->uniform_name(), max);
}

void Model::render(const RenderContext& context)
{
    if (!mesh_)
        return;

    for (uint8_t i = 0; i < textures_.size(); ++i)
        textures_[i]->use(i);

    bgfx::setTransform(glm::value_ptr(model_matrix_));
    mesh_->render(context);
}

NAMESPACE_RENDER_END
