#pragma once

#include <stdint.h>
#include <bgfx/bgfx.h>

#include "axgl/axgl.h"

NS_RENDER

struct RenderContext
{
    uint32_t width;
    uint32_t height;

    bgfx::ViewId view_id;
};

NS_RENDER_END
