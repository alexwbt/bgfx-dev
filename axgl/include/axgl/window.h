#pragma once

#include <unordered_map>
#include <memory>
#include <string>

struct GLFWwindow;

namespace glfw
{
    class Window final
    {
    private:
        static bool initialized_;
        static bool terminated_;
        static std::unordered_map<GLFWwindow*, Window*> windows_;

    public:
        static void initialize();
        static void terminate();

        static bool should_close_all();
        static void update_all();
        // static void RenderAll();

    private:
        static void glfw_error_callback(int error, const char* description);

        static void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
        static void cursor_pos_callback(GLFWwindow* glfw_window, double x, double y);
        static void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods);
        static void frame_buffer_size_callback(GLFWwindow* glfw_window, int width, int height);

        static Window* get_window(GLFWwindow* glfw_window);

    private:
        GLFWwindow* glfw_window_;

        // std::shared_ptr<EventListener> event_listener_;
        // std::shared_ptr<Renderer> renderer_;

        bool destroyed_ = false;

    public:
        Window(int width, int height, const std::string& title);
        ~Window();

    public:
        // void SetEventListener(std::shared_ptr<EventListener> event_listener);
        // void SetRenderer(std::shared_ptr<Renderer> renderer);

        void set_title(const std::string& title);

        GLFWwindow* get_glfw_window() const;

    private:
        // void Render();
        void destroy();
    };
}
