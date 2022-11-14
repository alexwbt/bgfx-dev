#pragma once

#include <vector>
#include <memory>

namespace gl
{
    class EventLoop
    {
    public:
        struct Component
        {
            virtual ~Component() {}
            virtual void initialize() {}
            virtual void terminate() {}
            virtual void update() {}
            virtual bool alive() { return true; }
        };

    private:
        std::vector<std::shared_ptr<Component>> components_;

    public:
        void add_component(std::shared_ptr<Component> component);

        void run();
    };
}
