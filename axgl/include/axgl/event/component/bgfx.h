#pragma once

#include "axgl/window.h"
#include "axgl/namespace.h"
#include "axgl/event/event_loop.h"

#include <string>
#include <memory>
#include <stdint.h>

NAMESPACE_EVENT

namespace comp
{
    class BgfxComponent : public Component
    {
    private:
        uint32_t width_;
        uint32_t height_;
        const std::string title_;

        std::shared_ptr<glfw::Window> window_;

    public:
        BgfxComponent(uint32_t width, uint32_t height, const std::string& title);

        void initialize() override;
        void terminate() override;
        void update() override;
        bool alive() override;

    protected:
        uint32_t width() { return width_; }
        uint32_t height() { return height_; }
        std::shared_ptr<const glfw::Window> window() { return window_; }
    };
}

NAMESPACE_EVENT_END
