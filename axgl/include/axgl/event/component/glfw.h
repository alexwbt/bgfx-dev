#pragma once

#include "axgl/axgl.h"
#include "axgl/event/event_loop.h"

NS_EVENT

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

NS_EVENT_END
