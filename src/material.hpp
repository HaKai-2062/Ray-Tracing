#pragma once

#include <glm/glm.hpp>

struct Material
{
	float Metallic = 1.0f;
	float Roughness = 1.0f;

	glm::vec3 Albedo{ 1.0f };
	glm::vec3 EmissionColor{ 0.0f };
	float EmissionPower = 2.0f;

	const glm::vec3 GetEmission() const { return EmissionColor * EmissionPower; }
};