#include "axgl/render/mesh.h"

NAMESPACE_RENDER

void Mesh::render(const RenderContext& context)
{
    bgfx::setVertexBuffer(0, vertex_buffer_);
    bgfx::setIndexBuffer(index_buffer_);

    bgfx::submit(context.view_id, shader_->get_program());
}

NAMESPACE_RENDER_END
