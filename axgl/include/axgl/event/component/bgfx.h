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
    public:
        struct Adapter : public glfw::Window::EventListener
        {
            struct InitializationContext
            {
                uint32_t width;
                uint32_t height;
                std::string title;
                std::shared_ptr<glfw::Window> window;
            };

            virtual ~Adapter() {}
            virtual void initialize(const InitializationContext& context) {}
            virtual void terminate() {}
            virtual void update() {}
        };

    private:
        uint32_t width_;
        uint32_t height_;
        const std::string title_;
        std::shared_ptr<Adapter> adapter_;
        std::shared_ptr<glfw::Window> window_;

    public:
        BgfxComponent(
            uint32_t width,
            uint32_t height,
            const std::string& title,
            std::shared_ptr<Adapter> adapter
        );
        virtual ~BgfxComponent() {}

        void initialize() override;
        void terminate() override;
        void update() override;
        bool alive() override;
    };
}

NAMESPACE_EVENT_END
