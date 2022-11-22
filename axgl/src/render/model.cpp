#include "axgl/render/model.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <bx/math.h>

#include "axgl/spdlog.h"

NAMESPACE_RENDER

void Model::set_mesh(std::shared_ptr<Mesh> mesh)
{
    mesh_ = std::move(mesh);
}

void Model::render(const RenderContext& context)
{
    if (!mesh_)
        return;

    glm::mat4 translation_matrix = glm::translate(glm::mat4(), translation);
    glm::mat4 rotation_matrix = glm::toMat4(glm::quat(rotation));
    glm::mat4 scale_matrix = glm::scale(scale);

    glm::mat4 model_matrix = translation_matrix;

    float translate_matrix[16];
    bx::mtxTranslate(
        translate_matrix,
        translation.x,
        translation.y,
        translation.z
    );
    bgfx::setTransform(translate_matrix);
    mesh_->render(context);
}

NAMESPACE_RENDER_END
