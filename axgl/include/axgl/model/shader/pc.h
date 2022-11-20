#pragma once

#include "axgl/model/shader_program.h"

namespace gl
{
    namespace shader
    {
        class PC : public ShaderProgram
        {
        public:
            struct Vertex
            {
                float x;
                float y;
                float z;
                uint32_t rgba;
            };

        public:
            PC() : ShaderProgram("vs_pc", "fs_pc") {}

            const bgfx::VertexLayout& get_layout() const override
            {
                static bgfx::VertexLayout layout;
                if (layout.getStride() == 0)
                {
                    layout.begin()
                        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
                        .end();
                }
                return layout;
            }
        };
    }
}
