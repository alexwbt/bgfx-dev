#include "axgl/event_loop.h"

namespace gl
{

    void EventLoop::add_component(std::shared_ptr<Component> component)
    {
        components_.push_back(std::move(component));
    }

    void EventLoop::run()
    {
        for (int i = 0; i < components_.size(); ++i)
            components_[i]->initialize();

        bool running;
        do
        {
            running = false;
            for (int i = 0; i < components_.size(); ++i)
            {
                if (components_[i]->alive())
                {
                    running = true;
                    components_[i]->update();
                }
            }
        } while (running);

        for (int i = components_.size() - 1; i >= 0; --i)
            components_[i]->terminate();
    }

}
