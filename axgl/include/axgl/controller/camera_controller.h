#pragma once

#include <memory>
#include <array>

#include "axgl/render/camera.h"
#include "axgl/namespace.h"

NAMESPACE_CONTROLLER

class SimpleCameraController
{
private:
    std::shared_ptr<gl::render::Camera> camera_;

    float camera_speed_ = 0.1f;

    float pivot_x_ = 0;
    float pivot_y_ = 0;
    float pivot_sensitivity_ = 0.1f;

public:
    void set_camera(std::shared_ptr<gl::render::Camera> camera);
    void move(const std::array<bool, 6>& controls);
    void pivot(float x, float y);
};

NAMESPACE_CONTROLLER_END
