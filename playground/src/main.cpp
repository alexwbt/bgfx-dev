#include <axgl/component/bgfx_window_component.h>

int main()
{
    auto bgfx_window_component = std::make_shared<gl::BgfxWindowComponent>(800, 600, "BGFX Window");

    gl::EventLoop event_loop;
    event_loop.add_component(bgfx_window_component);

    event_loop.run();
}
