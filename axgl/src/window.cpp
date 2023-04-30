#include "axgl/window.h"

#include <GLFW/glfw3.h>

#include "axgl/spdlog.h"

namespace glfw
{

    bool Window::initialized_ = false;
    bool Window::terminated_ = false;

    std::unordered_map<GLFWwindow*, Window*> Window::windows_;

    void Window::initialize()
    {
        if (initialized_ || terminated_)
            return;

        glfwSetErrorCallback(Window::glfw_error_callback);

        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW.");

        initialized_ = true;
    }

    void Window::terminate()
    {
        if (!initialized_ || terminated_)
            return;

        for (const auto& [glfw_window, window] : windows_)
            window->destroy();

        glfwTerminate();
        terminated_ = true;
    }

    bool Window::should_close_all()
    {
        for (const auto& [glfw_window, window] : windows_)
            if (!glfwWindowShouldClose(glfw_window))
                return false;
        return true;
    }

    void Window::update_all()
    {
        glfwPollEvents();

        // destroy closed windows
        for (auto it = windows_.begin(); it != windows_.end();)
        {
            const auto& glfw_window = it->first;
            const auto& window = it->second;
            if (window->destroyed_ || glfwWindowShouldClose(glfw_window))
            {
                it->second->destroy();
                it = windows_.erase(it);
            }
            else
                ++it;
        }
    }

    void Window::glfw_error_callback(int error, const char* description)
    {
        SPDLOG_DEBUG("GLFW Error {}: {}", error, description);
    }

    void Window::key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
    {
        auto* window = get_window(glfw_window);
        if (!window || !window->event_listener_)
            return;

        switch (action)
        {
        case GLFW_PRESS:    window->event_listener_->on_key_down(key); break;
        case GLFW_RELEASE:  window->event_listener_->on_key_down(key); break;
        }
    }

    void Window::cursor_pos_callback(GLFWwindow* glfw_window, double x, double y)
    {
        auto* window = get_window(glfw_window);
        if (window && window->event_listener_)
            window->event_listener_->on_mouse_move(x, y);
    }

    void Window::mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods)
    {
        auto* window = get_window(glfw_window);
        if (!window || !window->event_listener_)
            return;

        switch (action)
        {
        case GLFW_PRESS:    window->event_listener_->on_mouse_down(button); break;
        case GLFW_RELEASE:  window->event_listener_->on_key_down(button); break;
        }
    }

    void Window::frame_buffer_size_callback(GLFWwindow* glfw_window, int width, int height)
    {
        auto* window = get_window(glfw_window);
        if (window && window->event_listener_)
            window->event_listener_->on_resize(width, height);
    }

    Window* Window::get_window(GLFWwindow* glfw_window)
    {
        try
        {
            return windows_.at(glfw_window);
        }
        catch ([[maybe_unused]] const std::out_of_range& e)
        {
            SPDLOG_DEBUG("Tried to get GLFW window that does not exists. ({})", e.what());
            return nullptr;
        }
    }

    /* Non-static */

    Window::Window(int width, int height, const std::string& title)
    {
        if (!initialized_ || terminated_)
            throw std::runtime_error("Failed to create window, GLFW not initialized.");

        glfw_window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!glfw_window_)
            throw std::runtime_error("Failed to create window " + title + ".");

        glfwSetKeyCallback(glfw_window_, Window::key_callback);
        glfwSetCursorPosCallback(glfw_window_, Window::cursor_pos_callback);
        glfwSetMouseButtonCallback(glfw_window_, Window::mouse_button_callback);
        glfwSetFramebufferSizeCallback(glfw_window_, Window::frame_buffer_size_callback);

        windows_.insert({ glfw_window_, this });
    }

    Window::~Window()
    {
        destroy();
    }

    void Window::set_title(const std::string& title)
    {
        glfwSetWindowTitle(glfw_window_, title.c_str());
    }

    void Window::set_event_listener(std::shared_ptr<EventListener> event_listener)
    {
        event_listener_ = std::move(event_listener);
    }

    GLFWwindow* Window::get_glfw_window() const
    {
        return glfw_window_;
    }
    
    bool Window::key_pressed(int key) const
    {
        return glfwGetKey(glfw_window_, key) == GLFW_PRESS;
    }

    void Window::destroy()
    {
        if (!destroyed_)
        {
            glfwDestroyWindow(glfw_window_);
            destroyed_ = true;
        }
    }

}
