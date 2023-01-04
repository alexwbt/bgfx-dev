#include "axgl/render/texture.h"

#include <bimg/bimg.h>

#include "axgl/file.h"
#include "axgl/spdlog.h"

NAMESPACE_RENDER

bgfx::TextureHandle Texture::loadTexture2d(const std::string& file, uint64_t flags)
{
    auto data = readBinaryFile(file);
    auto size = static_cast<uint32_t>(data.size());

    bimg::ImageContainer image_container;
    bimg::imageParse(image_container, &data[0], size);

    auto format = static_cast<bgfx::TextureFormat::Enum>(image_container.m_format);

    if (!bgfx::isTextureValid(0, false, image_container.m_numLayers, format, flags))
    {
        SPDLOG_ERROR("Invalid texture. ({})", file);
        throw std::runtime_error("Invalid texture. (" + file + ")");
    }

    return bgfx::createTexture2D(
        static_cast<uint16_t>(image_container.m_width),
        static_cast<uint16_t>(image_container.m_height),
        false,
        1,
        bgfx::TextureFormat::Enum(image_container.m_format),
        flags,
        bgfx::copy(image_container.m_data, image_container.m_size)
    );
}

Texture::Texture(const std::string& uniform_name, const std::string& file)
    : uniform_name_(uniform_name)
{
    texture_ = loadTexture2d(file);
    texture_uniform_ = bgfx::createUniform(uniform_name.c_str(), bgfx::UniformType::Sampler);
}

Texture::~Texture()
{
    bgfx::destroy(texture_);
    bgfx::destroy(texture_uniform_);
}

void Texture::use(uint8_t stage) const
{
    bgfx::setTexture(stage, texture_uniform_, texture_);
}

NAMESPACE_RENDER_END
