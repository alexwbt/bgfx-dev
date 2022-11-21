#pragma once

#include <memory>
#include <vector>

#include <bgfx/bgfx.h>
#include <bx/math.h>

#include "axgl/render/model/shader_program.h"
#include "axgl/render/render_context.h"

NAMESPACE_RENDER

class Mesh
{
private:
    std::shared_ptr<ShaderProgram> shader_;
    bgfx::VertexBufferHandle vertex_buffer_;
    bgfx::IndexBufferHandle index_buffer_;

public:
    template<
        typename _ShaderProgram,
        std::enable_if_t<std::is_base_of_v<ShaderProgram, _ShaderProgram>, bool> = true>
    Mesh(
        std::shared_ptr<_ShaderProgram> shader,
        const std::vector<typename _ShaderProgram::Vertex>& vertices,
        const std::vector<uint16_t>& indices
    ) :
        shader_(shader),
        vertex_buffer_(
            bgfx::createVertexBuffer(
                bgfx::copy(
                    &vertices[0],
                    static_cast<uint32_t>(vertices.size()) * sizeof(typename _ShaderProgram::Vertex)
                ),
                shader->get_layout()
            )
        ),
        index_buffer_(bgfx::createIndexBuffer(
            bgfx::copy(&indices[0], static_cast<uint32_t>(indices.size()) * sizeof(uint16_t))))
    {}

    void render(const RenderContext& context);
};

NAMESPACE_RENDER_END
