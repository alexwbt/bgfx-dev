#pragma once

#include <string>

#include <bgfx/bgfx.h>

namespace gl
{
    class ShaderProgram
    {
    public:
        static const bgfx::ShaderHandle load_shader(const std::string& file);

    private:
        bgfx::ProgramHandle program_;

    public:
        ShaderProgram(
            const std::string& vertex_shader,
            const std::string& fragment_shader
        );
        virtual ~ShaderProgram() {}

        const bgfx::ProgramHandle& get_program() const
        {
            return program_;
        }

        virtual const bgfx::VertexLayout& get_layout() const = 0;
    };
}
