#pragma once

#include "axgl/namespace.h"
#include "axgl/event/event_loop.h"

NAMESPACE_EVENT

namespace comp
{
    class GlfwComponent : public Component
    {
    public:
        void initialize() override;
        void terminate() override;
        void update() override;
        bool alive() override;
    };
}

NAMESPACE_EVENT_END
