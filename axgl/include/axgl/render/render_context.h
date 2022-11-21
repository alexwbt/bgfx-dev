#pragma once

#include <stdint.h>
#include <bgfx/bgfx.h>

#include "axgl/namespace.h"

NAMESPACE_RENDER

struct RenderContext
{
    uint32_t width;
    uint32_t height;

    bgfx::ViewId view_id;
};

NAMESPACE_RENDER_END
