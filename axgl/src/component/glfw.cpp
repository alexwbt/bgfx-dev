#include "axgl/component/glfw.h"
#include "axgl/window.h"

namespace gl
{
    void GlfwComponent::initialize()
    {
        glfw::Window::initialize();
    }

    void GlfwComponent::terminate()
    {
        glfw::Window::terminate();
    }

    void GlfwComponent::update()
    {
        glfw::Window::update_all();
    }

    bool GlfwComponent::alive()
    {
        return !glfw::Window::should_close_all();
    }
}
