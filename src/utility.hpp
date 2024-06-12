#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

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