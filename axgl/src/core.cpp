#include "axgl/core.h"

namespace gl
{
    namespace core
    {

        void Core::add_component(std::shared_ptr<Component> component)
        {
            components_.push_back(std::move(component));
        }

        void Core::initialize()
        {
            for (const auto& component : components_)
                component->initialize();
        }

        void Core::terminate()
        {
            for (auto it = components_.rbegin(); it != components_.rend(); ++it)
                (*it)->terminate();
        }

        void Core::update()
        {
            for (const auto& component : components_)
                if (component->alive())
                    component->update();
        }

        bool Core::alive()
        {
            for (const auto& component : components_)
                if (component->alive())
                    return true;
            return false;
        }

        void Core::run()
        {
            initialize();

            while (alive())
                update();

            terminate();
        }

    }
}
