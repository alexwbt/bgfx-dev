#include <axgl/component/glfw.h>
#include <axgl/component/bgfx.h>
#include <axgl/core.h>

#include <bgfx/bgfx.h>

class Playground : public gl::BgfxComponent
{
    // std::shared_ptr<

public:
    Playground() : gl::BgfxComponent(800, 600, "Hello BGFX!") {}

    void initialize() override
    {
        gl::BgfxComponent::initialize();

        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
    }

    void update() override
    {
        gl::BgfxComponent::update();

        bgfx::touch(0);
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
