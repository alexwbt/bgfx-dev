#pragma once

#ifndef NDEBUG
#   define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include <spdlog/spdlog.h>

#include "axgl/namespace.h"

NAMESPACE_GL

namespace spdlog
{
    inline void init()
    {
        ::spdlog::set_level(::spdlog::level::trace);
    }
}

NAMESPACE_GL_END
