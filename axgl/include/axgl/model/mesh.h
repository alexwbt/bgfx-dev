#pragma once

#include <memory>
#include <vector>

#include <bgfx/bgfx.h>
#include <bx/math.h>

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
            std::enable_if_t<std::is_base_of_v<ShaderProgram, _ShaderProgram>, bool> = true>
        Mesh(
            std::shared_ptr<_ShaderProgram> shader,
            const std::vector<typename _ShaderProgram::Vertex>& vertices,
            const std::vector<uint16_t>& indices
        ) :
            shader_(shader),
            vertex_buffer_(bgfx::createVertexBuffer(
                bgfx::copy(&vertices[0], vertices.size() * sizeof(_ShaderProgram::Vertex)),
                shader->get_layout())),
            index_buffer_(bgfx::createIndexBuffer(
                bgfx::copy(&indices[0], indices.size() * sizeof(uint16_t))))
        {}

        void test()
        {
            // float mtx[16];
            // bx::mtxRotateY(mtx, 0.0f);

            // // position x,y,z
            // mtx[12] = 0.0f;
            // mtx[13] = 0.0f;
            // mtx[14] = 0.0f;

            // // Set model matrix for rendering.
            // bgfx::setTransform(mtx);

            // Set vertex and index buffer.
            bgfx::setVertexBuffer(0, vertex_buffer_);
            bgfx::setIndexBuffer(index_buffer_);

            // Set render states.
            // bgfx::setState(BGFX_STATE_DEFAULT);

            // Submit primitive for rendering to view 0.
            bgfx::submit(0, shader_->get_program());
        }
    };
}
