#pragma once

#include "axgl/namespace.h"
#include "axgl/render/shader_program.h"

NAMESPACE_RENDER

namespace shader
{
    class PNTT : public ShaderProgram
    {
    public:
        struct Vertex
        {
            float x, y, z;
            uint32_t normal, tangent;
            int16_t u, v;
        };

    public:
        PNTT() : ShaderProgram("vs_pntt", "fs_pntt") {}

        const bgfx::VertexLayout& get_layout() const override
        {
            static bgfx::VertexLayout layout;
            if (layout.getStride() == 0)
            {
                layout.begin()
                    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                    .add(bgfx::Attrib::Normal, 4, bgfx::AttribType::Uint8, true, true)
                    .add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Uint8, true, true)
                    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
                    .end();
            }
            return layout;
        }
    };
}

NAMESPACE_RENDER_END
