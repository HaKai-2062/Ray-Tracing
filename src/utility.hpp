#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

#include <glm/glm.hpp>

// Utility Functions

namespace Utility
{
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

    inline float RandomFloat(float min, float max)
    {
        static std::mt19937 generator{ std::random_device{}() };
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(generator);
    }

    inline glm::vec3 RandomVec3(float min, float max)
    {
        return glm::vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
    }
}

