#include "axgl/controller/camera_controller.h"

NAMESPACE_CONTROLLER

void SimpleCameraController::set_camera(std::shared_ptr<gl::render::Camera> camera)
{
    camera_ = std::move(camera);
}

void SimpleCameraController::move(const std::array<bool, 6>& controls)
{
    if (!camera_) return;
    if (controls[0]) camera_->position += camera_speed_ * camera_->front();
    if (controls[1]) camera_->position -= camera_speed_ * camera_->front();
    if (controls[2]) camera_->position += camera_speed_ * camera_->right();
    if (controls[3]) camera_->position -= camera_speed_ * camera_->right();
    if (controls[4]) camera_->position += camera_speed_ * glm::vec3(0, 1, 0);
    if (controls[5]) camera_->position -= camera_speed_ * glm::vec3(0, 1, 0);

    camera_->update_transform();
}

void SimpleCameraController::pivot(float x, float y)
{
    if (!camera_) return;
    if (pivot_x_ || pivot_y_)
    {
        camera_->yaw += (x - pivot_x_) * pivot_sensitivity_;
        camera_->pitch += (pivot_y_ - y) * pivot_sensitivity_;
    }
    pivot_x_ = x;
    pivot_y_ = y;

    if (camera_->pitch > 89.0f) camera_->pitch = 89.0f;
    if (camera_->pitch < -89.0f) camera_->pitch = -89.0f;

    camera_->update_transform();
}

NAMESPACE_CONTROLLER_END
