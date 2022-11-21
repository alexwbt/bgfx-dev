#pragma once

#include <vector>
#include <memory>

#include "axgl/namespace.h"

NAMESPACE_EVENT

struct Component
{
    virtual ~Component() {}
    virtual void initialize() {}
    virtual void terminate() {}
    virtual void update() {}
    virtual bool alive() { return false; }
};

class EventLoop : public Component
{
    std::vector<std::shared_ptr<Component>> components_;

public:
    void add_component(std::shared_ptr<Component> component);

    void initialize() override;
    void terminate() override;
    void update() override;
    bool alive() override;

    void run();
};

NAMESPACE_EVENT_END
