#include <axgl/event/component/glfw.h>
#include <axgl/event/component/bgfx.h>
#include <axgl/event/event_loop.h>

#include <axgl/render/render_context.h>
#include <axgl/render/model/mesh.h>
#include <axgl/render/camera.h>

#include <bgfx/bgfx.h>

#include "data.h"

class Playground : public gl::event::comp::BgfxComponent
{
    std::shared_ptr<gl::render::Mesh> cube;
    gl::render::Camera camera;
    int counter = 0;

public:
    Playground() : gl::event::comp::BgfxComponent(800, 600, "Hello BGFX!") {}

    void initialize() override
    {
        gl::event::comp::BgfxComponent::initialize();

        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

        auto shader = std::make_shared<gl::render::shader::PC>();
        cube = std::make_shared<gl::render::Mesh>(shader, cube_vertices, cube_indices);

        camera.position = { -5.0f , 0.0f , 0.0f };
    }

    void update() override
    {
        gl::event::comp::BgfxComponent::update();

        gl::render::RenderContext context{ width(), height(), 0 };
        // camera.yaw++;
        camera.update();
        camera.use(context);

        // render
        bgfx::touch(0);

        float mtx[16];
        ++counter;
        bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
        bgfx::setTransform(mtx);

        cube->render(context);

        bgfx::frame();
    }
};

int main()
{
    auto glfw = std::make_shared<gl::event::comp::GlfwComponent>();
    auto playground = std::make_shared<Playground>();

    gl::event::EventLoop core;
    core.add_component(glfw);
    core.add_component(playground);
    core.run();
}
