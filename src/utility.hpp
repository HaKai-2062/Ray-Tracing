#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

#include <glm/glm.hpp>

// Utility Functions

inline float degreesToRadians(float degrees)
{
    return degrees * glm::pi<float>() / 180.0f;
}

inline uint32_t ConvertToRGBA(const glm::vec4& color)
{
    uint8_t r = static_cast<uint8_t>(color.r * 255.0f);
    uint8_t g = static_cast<uint8_t>(color.g * 255.0f);
    uint8_t b = static_cast<uint8_t>(color.b * 255.0f);
    uint8_t a = static_cast<uint8_t>(color.a * 255.0f);

    uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
    return result;
}