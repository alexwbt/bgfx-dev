#include <axgl/controller/camera_controller.h>
#include <axgl/controller/timestep_controller.h>

#include <axgl/event/component/glfw.h>
#include <axgl/event/component/bgfx.h>
#include <axgl/event/event_loop.h>

#include <axgl/render/render_context.h>
#include <axgl/render/camera.h>
#include <axgl/render/model.h>
#include <axgl/render/mesh.h>

#include <axgl/spdlog.h>

#include <glm/glm.hpp>
#include <bgfx/bgfx.h>
#include <glfw/glfw3.h>

#include "data.h"

class Playground : public gl::event::comp::BgfxComponent::Adapter
{
private:
    uint32_t width_ = 0;
    uint32_t height_ = 0;
    std::shared_ptr<glfw::Window> window_;
    const bgfx::ViewId view_id_ = 0;

    gl::ctrl::TimestepController timestep_controller_;

    std::shared_ptr<gl::render::Camera> camera_;
    gl::ctrl::SimpleCameraController camera_controller_;

    gl::render::Model cube_;

public:
    void initialize(const InitializationContext& context) override
    {
        window_ = context.window;
        glfwSetInputMode(
            window_->get_glfw_window(),
            GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        width_ = context.width;
        height_ = context.height;
        bgfx::setViewRect(view_id_, 0, 0, width_, height_);
        bgfx::setViewClear(view_id_, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

        camera_ = std::make_shared<gl::render::Camera>();
        camera_->position = { 0.0f, 0.0f, -5.0f };
        camera_->yaw = 90.0f;
        camera_->update_transform();
        camera_controller_.set_camera(camera_);

        auto shader = std::make_shared<gl::render::shader::PC>();
        auto cube_mesh = std::make_shared<gl::render::Mesh>(shader, cube_vertices, cube_indices);
        cube_.set_mesh(cube_mesh);

        timestep_controller_.initialize();
        timestep_controller_.set_update_function(std::bind(&Playground::tick, this));
        timestep_controller_.set_render_function(std::bind(&Playground::render, this));
    }

    void on_resize(int width, int height) override
    {
        if (width != width_ || height != height_)
        {
            width_ = static_cast<uint32_t>(width);
            height_ = static_cast<uint32_t>(height);
            bgfx::reset(width_, height_, BGFX_RESET_VSYNC);
            bgfx::setViewRect(view_id_, 0, 0, width_, height_);
        }
    }

    void on_mouse_move(double x, double y) override
    {
        camera_controller_.pivot(
            static_cast<float>(x),
            static_cast<float>(y)
        );
    }

    void update() override
    {
        timestep_controller_.update();
    }

    void tick()
    {
        camera_controller_.move({
            glfwGetKey(window_->get_glfw_window(), GLFW_KEY_W) == GLFW_PRESS,
            glfwGetKey(window_->get_glfw_window(), GLFW_KEY_S) == GLFW_PRESS,
            glfwGetKey(window_->get_glfw_window(), GLFW_KEY_D) == GLFW_PRESS,
            glfwGetKey(window_->get_glfw_window(), GLFW_KEY_A) == GLFW_PRESS,
            glfwGetKey(window_->get_glfw_window(), GLFW_KEY_SPACE) == GLFW_PRESS,
            glfwGetKey(window_->get_glfw_window(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS });

        // cube_.rotation += glm::vec3(-0.01f, 0, -0.01f);
        // cube_.update_transform();
    }

    void render()
    {
        gl::render::RenderContext context{
            width_,
            height_,
            view_id_
        };

        bgfx::touch(view_id_);
        camera_->use(context);
        cube_.render(context);
        bgfx::frame();
    }
};

int main()
{
    gl::log::init();

    auto playground = std::make_shared<Playground>();

    using namespace gl::event::comp;
    auto glfw = std::make_shared<GlfwComponent>();
    auto bgfx = std::make_shared<BgfxComponent>(800, 600, "Hello BGFX!", playground);

    gl::event::EventLoop core;
    core.add_component(glfw);
    core.add_component(bgfx);
    core.run();
}
