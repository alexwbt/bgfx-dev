#pragma once

#include "axgl/core.h"
#include "axgl/window.h"

#include <string>
#include <memory>
#include <stdint.h>

namespace gl
{
    class BgfxComponent : public core::Component
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
    };
}
