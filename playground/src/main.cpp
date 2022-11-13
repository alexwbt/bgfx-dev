#include <iostream>

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <GLFW/glfw3.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>
#include "window.h"
#include "logo.h"

int main()
{
    try
    {
        gl::Window::initialize();
        gl::Window window1(800, 600, "window1");
        gl::Window window2(300, 300, "window2");

        bgfx::renderFrame();
        // Initialize bgfx using the native window handle and window resolution.
        bgfx::Init init;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        init.platformData.ndt = glfwGetX11Display();
        init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window1.get_glfw_window());
#elif BX_PLATFORM_OSX
        init.platformData.nwh = glfwGetCocoaWindow(window1.get_glfw_window());
#elif BX_PLATFORM_WINDOWS
        init.platformData.nwh = glfwGetWin32Window(window1.get_glfw_window());
#endif

        int width, height;
        glfwGetWindowSize(window1.get_glfw_window(), &width, &height);
        init.resolution.width = (uint32_t)width;
        init.resolution.height = (uint32_t)height;
        init.resolution.reset = BGFX_RESET_VSYNC;
        if (!bgfx::init(init))
            return 1;

        std::cout << "bgfx initialized" << std::endl;
        std::cout << "window size: " << width << ", " << height << std::endl;

        // Set view 0 to the same dimensions as the window and to clear the color buffer.
        const bgfx::ViewId clear_view = 0;
        bgfx::setViewClear(clear_view, BGFX_CLEAR_COLOR);
        bgfx::setViewRect(clear_view, 0, 0, bgfx::BackbufferRatio::Equal);

        while (!gl::Window::should_close_all())
        {
            gl::Window::update_all();

            // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
            bgfx::touch(clear_view);
            // Use debug font to print information about this example.
            bgfx::dbgTextClear();
            bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(width / 2 / 8), 20) - 20, bx::max<uint16_t>(uint16_t(height / 2 / 16), 6) - 6, 40, 12, s_logo, 160);
            bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
            bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
            bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
            bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
            const bgfx::Stats* stats = bgfx::getStats();
            bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
            // Enable stats or debug text.
            bool show_status = false;
            bgfx::setDebug(show_status ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
            // Advance to next frame. Process submitted rendering primitives.
            bgfx::frame();
        }
        bgfx::shutdown();

        gl::Window::terminate();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
}
