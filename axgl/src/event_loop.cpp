#include "axgl/event_loop.h"

namespace gl
{
    namespace event
    {

        void EventLoop::add_component(std::shared_ptr<Component> component)
        {
            components_.push_back(std::move(component));
        }

        void EventLoop::initialize()
        {
            for (const auto& component : components_)
                component->initialize();
        }

        void EventLoop::terminate()
        {
            for (auto it = components_.rbegin(); it != components_.rend(); ++it)
                (*it)->terminate();
        }

        void EventLoop::update()
        {
            for (const auto& component : components_)
                if (component->alive())
                    component->update();
        }

        bool EventLoop::alive()
        {
            for (const auto& component : components_)
                if (component->alive())
                    return true;
            return false;
        }

        void EventLoop::run()
        {
            initialize();

            while (alive())
            {
                update();
            }

            terminate();
        }

    }
}
