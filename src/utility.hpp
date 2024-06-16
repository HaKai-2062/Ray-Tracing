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
    
    /*
    uint32_t RANDOM_SEED = 0;
    
    inline static uint32_t PCG_Hash()
    {
        uint32_t state = RANDOM_SEED * 747796405u + 2891336453u;
        uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
        return (word >> 22u) ^ word;
    }

    inline float RandomFloat(float min, float max)
    {
        RANDOM_SEED = PCG_Hash();
        float randFloat_0to1 = (float)RANDOM_SEED / (float)std::numeric_limits<uint32_t>::max();

        return randFloat_0to1 * (max - min) * (max - min) * 0.5;
    }*/
    
    inline float RandomFloat(float min, float max)
    {
        static thread_local std::mt19937 generator{ std::random_device{}() };
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(generator);
    }

    inline glm::vec3 RandomVec3(float min, float max)
    {
        return glm::vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
    }

    inline glm::vec3 RandomInUnitSphere()
    {
        while (true)
        {
            glm::vec3 p = RandomVec3(-1.0f, 1.0f);
            if (glm::dot(p,p) < 1)
                return p;
        }
    }

    inline glm::vec3 RandomOnHemisphere(const glm::vec3& normal)
    {
        glm::vec3 onUnitSphere = glm::normalize(RandomInUnitSphere());
        if (glm::dot(onUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
            return onUnitSphere;
        else
            return -onUnitSphere;
    }

    // Approximation of contribution of the Fresnel factor in the specular reflection of light
    float FresnelSchlick(float cosTheta, float refIdx)
    {
    	float r0 = (1.0f - refIdx) / (1.0f + refIdx);
        r0 = r0 * r0;
	    return r0 + (1.0f - r0) * pow(1.0f - cosTheta, 5.0f);
    }

}

