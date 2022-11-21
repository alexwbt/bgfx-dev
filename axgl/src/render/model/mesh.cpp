#include "axgl/render/model/mesh.h"

NS_RENDER

void Mesh::render(const RenderContext& context)
{
    bgfx::setVertexBuffer(0, vertex_buffer_);
    bgfx::setIndexBuffer(index_buffer_);

    bgfx::submit(context.view_id, shader_->get_program());
}

NS_RENDER_END
