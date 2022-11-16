#pragma once

#include <string>

#include <bgfx/bgfx.h>

namespace gl
{
    class ShaderProgram
    {
    public:
        static bgfx::ShaderHandle load_shader(const char* const FILE_NAME)
        {
        }

    private:
        bgfx::ProgramHandle program_;

    public:
        ShaderProgram(
            const std::string& vertex_shader,
            const std::string& fragment_shader
        );

        const bgfx::ProgramHandle& get_program()
        {
            return program_;
        }
    };
}
