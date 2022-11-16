#pragma once

#include "axgl/core.h"

namespace gl
{
    class GlfwComponent : public core::Component
    {
    public:
        void initialize() override;
        void terminate() override;
        void update() override;
        bool alive() override;
    };
}
