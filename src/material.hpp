#pragma once

#include <glm/glm.hpp>

struct Material
{
	float Metallic = 1.0f;
	float Roughness = 1.0;

	glm::vec3 Albedo{ 1.0f };
};