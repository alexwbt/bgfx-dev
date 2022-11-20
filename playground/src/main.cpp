#include <axgl/component/glfw.h>
#include <axgl/component/bgfx.h>
#include <axgl/core.h>

#include <axgl/model/mesh.h>
#include <axgl/camera.h>

#include <bgfx/bgfx.h>

#include "data.h"

class Playground : public gl::BgfxComponent
{
    std::shared_ptr<gl::Mesh> cube;
    gl::Camera camera;
    int counter = 0;

public:
    Playground() : gl::BgfxComponent(800, 600, "Hello BGFX!") {}

    void initialize() override
    {
        gl::BgfxComponent::initialize();

        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

        auto shader = std::make_shared<gl::shader::PC>();
        cube = std::make_shared<gl::Mesh>(shader, cube_vertices, cube_indices);

        camera.direction = { 0.0f , 0.0f , -1.0f };
    }

    void update() override
    {
        gl::BgfxComponent::update();

        bgfx::touch(0);

        const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
        const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
        float view[16];
        bx::mtxLookAt(view, eye, at);
        float proj[16];
        bx::mtxProj(proj, 60.0f, float(800) / float(600), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);

        float mtx[16];
        ++counter;
        bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
        bgfx::setTransform(mtx);  
        cube->test();

        bgfx::frame();
    }
};

int main()
{
    auto glfw = std::make_shared<gl::GlfwComponent>();
    auto playground = std::make_shared<Playground>();

    gl::core::Core core;
    core.add_component(glfw);
    core.add_component(playground);
    core.run();
}
