#include "axgl/render/shader_program.h"

#include <stdint.h>

#include "axgl/file.h"

NAMESPACE_RENDER

const bgfx::ShaderHandle ShaderProgram::load_shader(const std::string& name)
{
    std::string prefix = "./res/shader/";
    switch (bgfx::getRendererType()) {
    case bgfx::RendererType::Noop:          break;
    case bgfx::RendererType::Direct3D9:     prefix += "dx9_";   break;
    case bgfx::RendererType::Direct3D11:
    case bgfx::RendererType::Direct3D12:    prefix += "dx11_";  break;
    case bgfx::RendererType::Gnm:           prefix += "pssl_";  break;
    case bgfx::RendererType::Metal:         prefix += "metal_"; break;
    case bgfx::RendererType::OpenGL:        prefix += "glsl_";  break;
    case bgfx::RendererType::OpenGLES:      prefix += "essl_";  break;
    case bgfx::RendererType::Vulkan:        prefix += "spirv_"; break;
    }

    auto buffer = readBinaryFile(prefix + name + ".bin");
    // might need to append '\0' at the end of the data
    // buffer.push_back('\0');

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

ShaderProgram::~ShaderProgram()
{
    bgfx::destroy(program_);
}

const bgfx::ProgramHandle& ShaderProgram::get_program() const
{
    return program_;
}

NAMESPACE_RENDER_END
