#pragma once

#include <glm/glm.hpp>

struct Material
{
	float Metallic = 1.0f;
	float Roughness = 1.0f;

	glm::vec3 Albedo{ 1.0f };
	glm::vec3 EmissionColor{ 1.0f };
	float EmissionPower = 0.0f;

	const glm::vec3 GetEmission() const { return EmissionColor * EmissionPower; }
};