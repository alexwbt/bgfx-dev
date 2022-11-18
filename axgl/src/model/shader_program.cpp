#include "axgl/model/shader_program.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>

#include <bgfx/bgfx.h>


namespace gl
{

    const bgfx::ShaderHandle ShaderProgram::load_shader(const std::string& file)
    {
        std::ifstream input(file, std::ios::binary);
        // TODO: might need to append '\0' at the end of the data
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(input), {});

        const bgfx::Memory* data = bgfx::copy(&buffer[0], static_cast<uint32_t>(buffer.size()));

        return bgfx::createShader(data);
    }

    ShaderProgram::ShaderProgram(
        const std::string& vertex_shader,
        const std::string& fragment_shader)
    {
        bgfx::ShaderHandle vsh = load_shader(vertex_shader);
        bgfx::ShaderHandle fsh = load_shader(fragment_shader);
        program_ = bgfx::createProgram(vsh, fsh, true);
    }

}
