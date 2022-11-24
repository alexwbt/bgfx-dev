#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <stdint.h>
#include <exception>

#include "axgl/spdlog.h"
#include "axgl/namespace.h"

NAMESPACE_GL

inline std::vector<uint8_t> readBinaryFile(const std::string& file)
{
    std::ifstream input(file, std::ios::binary);
    if (!input.is_open())
    {
        SPDLOG_ERROR("Failed to open file. ({})", file);
        throw std::runtime_error("Failed to open file. (" + file + ")");
    }

    std::vector<uint8_t> data(std::istreambuf_iterator<char>(input), {});
    return data;
}

NAMESPACE_GL_END
