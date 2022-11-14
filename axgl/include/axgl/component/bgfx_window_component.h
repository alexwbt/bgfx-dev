#include "axgl/event_loop.h"
#include "axgl/window.h"

#include <memory>
#include <string>
#include <stdint.h>

namespace gl
{
    class BgfxWindowComponent : public event::Component
    {
    private:
        std::shared_ptr<glfw::Window> window_;

        const uint32_t width_;
        const uint32_t height_;
        const std::string title_;

        const uint16_t clear_view_;

    public:
        BgfxWindowComponent(uint32_t width, uint32_t height, const std::string& title);

        void initialize() override;
        void terminate() override;
        void update() override;
        bool alive() override;
    };
}
