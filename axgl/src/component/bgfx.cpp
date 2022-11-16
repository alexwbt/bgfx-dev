#include "axgl/component/bgfx.h"

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

    BgfxComponent::BgfxComponent(uint32_t width, uint32_t height, const std::string& title)
        : width_(width), height_(height), title_(title) {}


    void BgfxComponent::initialize()
    {
        window_ = std::make_shared<glfw::Window>(width_, height_, title_);

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
    }

    void BgfxComponent::terminate()
    {
        bgfx::shutdown();
    }

    void BgfxComponent::update()
    {}

    bool BgfxComponent::alive()
    {
        return !window_->is_destroyed();
    }

}
