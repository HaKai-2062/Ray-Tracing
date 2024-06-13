#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

// Custom Headers
#include "ray.hpp"
#include "interval.hpp"

// Utility Functions

inline float degreesToRadians(float degrees)
{
    return degrees * glm::pi<float>() / 180.0f;
}

inline float randomFloat(float min = 0.0f, float max = 1.0f)
{
    std::uniform_real_distribution distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline glm::vec3 randomVector(float min = -1.0f, float max = 1.0f)
{
    return glm::vec3(randomFloat(), randomFloat(), randomFloat());
}

inline glm::vec3 randOnHemisphere(const glm::vec3& normal)
{
    while (true)
    {
        glm::vec3 p =  randomVector();
        if (glm::dot(p, p) < 1)
        {
            glm::vec3 unitVector = glm::normalize(p);
            return glm::dot(unitVector, normal) < 0 ? unitVector : -unitVector;
        }
    }
}