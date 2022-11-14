#include "axgl/component/bgfx_window_component.h"

#include <stdexcept>

// bgfx
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

// glfw
#include <GLFW/glfw3.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

namespace gl
{

    BgfxWindowComponent::BgfxWindowComponent(uint32_t width, uint32_t height, const std::string& title)
        : window_(nullptr), width_(width), height_(height), title_(title), clear_view_(0)
    {}

    void BgfxWindowComponent::initialize()
    {
        gl::Window::initialize();
        window_ = std::make_shared<Window>(width_, height_, "BGFX");

        // Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
        // Most graphics APIs must be used on the same thread that created the window.
        bgfx::renderFrame();

        // Initialize bgfx using the native window handle and window resolution.
        bgfx::Init init;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        init.platformData.ndt = glfwGetX11Display();
        init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window_->get_glfw_window());
#elif BX_PLATFORM_OSX
        init.platformData.nwh = glfwGetCocoaWindow(window_->get_glfw_window());
#elif BX_PLATFORM_WINDOWS
        init.platformData.nwh = glfwGetWin32Window(window_->get_glfw_window());
#endif
        init.resolution.width = width_;
        init.resolution.height = height_;
        init.resolution.reset = BGFX_RESET_VSYNC;

        if (!bgfx::init(init))
            throw std::runtime_error("Failed to initialize bgfx.");

        bgfx::setViewClear(clear_view_, BGFX_CLEAR_COLOR);
        bgfx::setViewRect(clear_view_, 0, 0, bgfx::BackbufferRatio::Equal);
    }

    void BgfxWindowComponent::terminate()
    {
        bgfx::shutdown();
        gl::Window::terminate();
    }

    void BgfxWindowComponent::update()
    {
        gl::Window::update_all();

        // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
        bgfx::touch(clear_view_);
        // Use debug font to print information about this example.
        bgfx::dbgTextClear();
        // bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(width / 2 / 8), 20) - 20, bx::max<uint16_t>(uint16_t(height / 2 / 16), 6) - 6, 40, 12, s_logo, 160);
        bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
        bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
        bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
        bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
        const bgfx::Stats* stats = bgfx::getStats();
        bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
        // Enable stats or debug text.
        // bgfx::setDebug(s_showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
        bgfx::setDebug(BGFX_DEBUG_STATS);
        // Advance to next frame. Process submitted rendering primitives.
        bgfx::frame();
    }

    bool BgfxWindowComponent::alive()
    {
        return !gl::Window::should_close_all();
    }

}
