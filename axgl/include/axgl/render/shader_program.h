#pragma once

#include <string>
#include <bgfx/bgfx.h>

#include "axgl/namespace.h"

NAMESPACE_RENDER

class ShaderProgram
{
public:
    static const bgfx::ShaderHandle load_shader(const std::string& name);

private:
    bgfx::ProgramHandle program_;

public:
    ShaderProgram(
        const std::string& vertex_shader,
        const std::string& fragment_shader
    );
    virtual ~ShaderProgram();

    const bgfx::ProgramHandle& get_program() const;

    virtual const bgfx::VertexLayout& get_layout() const = 0;
};

NAMESPACE_RENDER_END
