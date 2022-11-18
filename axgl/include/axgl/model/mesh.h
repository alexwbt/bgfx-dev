#pragma once

#include <memory>
#include <vector>

#include <bgfx/bgfx.h>

#include "axgl/model/shader_program.h"

namespace gl
{
    class Mesh
    {
    private:
        std::shared_ptr<ShaderProgram> shader_;
        bgfx::VertexBufferHandle vertex_buffer_;
        bgfx::IndexBufferHandle index_buffer_;

    public:
        template<
            typename _ShaderProgram,
            std::enable_if_t<std::is_base_of<ShaderProgram, _ShaderProgram>::value>
        >
        Mesh(
            std::shared_ptr<_ShaderProgram> shader,
            const std::vector<typename _ShaderProgram::Vertex>& vertices,
            const std::vector<uint16_t>& indices
        ) :
            shader_(shader),

            vertex_buffer_(bgfx::createVertexBuffer(
                bgfx::copy(&vertices[0], vertices.size()),
                shader->get_layout())),

            index_buffer_(bgfx::createIndexBuffer(
                bgfx::copy(&indices[0], indices.size())))
        {}
    };
}
