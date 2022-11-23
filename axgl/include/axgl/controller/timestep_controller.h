#pragma once

#include <chrono>
#include <stdint.h>
#include <functional>

#include "axgl/namespace.h"

NAMESPACE_CONTROLLER

class TimestepController
{
private:
    static constexpr int64_t kOneSecond = 1000000000;
    static constexpr double kTimestep = kOneSecond / 60.0;

private:
    std::function<void()> update_function_;
    std::function<void()> render_function_;

    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point update_timer;
    double delta_time = 0.0;
    int update_counter = 0;

public:
    void set_update_function(std::function<void()> update_function)
    {
        update_function_ = std::move(update_function);
    }

    void set_render_function(std::function<void()> render_function)
    {
        render_function_ = std::move(render_function);
    }

    void initialize()
    {
        start_time = std::chrono::high_resolution_clock::now();
        update_timer = std::chrono::high_resolution_clock::now();
    }

    void update()
    {
        auto now = std::chrono::high_resolution_clock::now();
        delta_time += (double)std::chrono::duration_cast<std::chrono::nanoseconds>(now - start_time).count() / kTimestep;
        start_time = now;

        if (delta_time < 0)
            return;

        while (delta_time >= 1)
        {
            update_function_();
            update_counter++;
            delta_time--;
        }

        render_function_();
    }
};

NAMESPACE_CONTROLLER_END
