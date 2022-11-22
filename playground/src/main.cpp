#include <axgl/event/component/glfw.h>
#include <axgl/event/component/bgfx.h>
#include <axgl/event/event_loop.h>

#include <axgl/render/render_context.h>
#include <axgl/render/camera.h>
#include <axgl/render/model.h>
#include <axgl/render/mesh.h>

#include <axgl/spdlog.h>

#include <bgfx/bgfx.h>

#include "data.h"

class Playground : public gl::event::comp::BgfxComponent::Adapter
{
private:
    int tick = 0;

    uint32_t width_ = 0;
    uint32_t height_ = 0;
    const bgfx::ViewId view_id_ = 0;

    gl::render::Camera camera_;
    // std::shared_ptr<gl::render::Mesh> cube_;
    gl::render::Model cube_;

public:
    void initialize() override
    {
        bgfx::setViewClear(view_id_, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

        auto shader = std::make_shared<gl::render::shader::PC>();
        auto cube_mesh = std::make_shared<gl::render::Mesh>(shader, cube_vertices, cube_indices);
        cube_.set_mesh(cube_mesh);

        camera_.position = { -5.0f, 0.0f, 0.0f };
        // cube_.translation += glm::vec3(0, 2, 0);
    }

    void update() override
    {
        ++tick;

        gl::render::RenderContext context{
            width_,
            height_,
            view_id_
        };

        camera_.update();
        camera_.use(context);

        // cube_.rotation += glm::vec3(0.01f, 0.01f, 0.01f);

        // render
        bgfx::touch(view_id_);
        cube_.render(context);
        bgfx::frame();
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
