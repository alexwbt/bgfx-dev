#include "axgl/render/mesh.h"

NAMESPACE_RENDER

void Mesh::render(const RenderContext& context)
{
    bgfx::setVertexBuffer(0, vertex_buffer_);
    bgfx::setIndexBuffer(index_buffer_);

    bgfx::setState(
        BGFX_STATE_WRITE_R |
        BGFX_STATE_WRITE_G |
        BGFX_STATE_WRITE_B |
        BGFX_STATE_WRITE_A |
        BGFX_STATE_WRITE_Z |
        BGFX_STATE_DEPTH_TEST_LESS |
        BGFX_STATE_CULL_CCW |
        BGFX_STATE_MSAA
    );
    bgfx::submit(context.view_id, shader_->get_program());
}

NAMESPACE_RENDER_END
