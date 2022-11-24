#pragma once

#include <string>

#include <bgfx/bgfx.h>

#include "axgl/namespace.h"

NAMESPACE_RENDER

class Texture
{
public:
    static bgfx::TextureHandle loadTexture2d(const std::string& file, uint64_t flags = 0);

private:
    bgfx::TextureHandle texture_;

    std::string uniform_name_;
    bgfx::UniformHandle texture_uniform_;

public:
    Texture(const std::string& uniform_name, const std::string& file);
    ~Texture();

    std::string uniform_name() const { return uniform_name_; };
    void use(uint8_t stage) const;
};

NAMESPACE_RENDER_END
