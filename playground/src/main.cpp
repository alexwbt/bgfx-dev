#include <axgl/component/bgfx_window_component.h>

int main()
{
    auto bgfx_window_component = std::make_shared<gl::BgfxWindowComponent>(800, 600, "BGFX Window");

    gl::event::EventLoop core_event_loop;
    core_event_loop.add_component(bgfx_window_component);

    core_event_loop.run();
}
