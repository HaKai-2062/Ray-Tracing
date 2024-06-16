#pragma once

#include <glm/glm.hpp>

struct Material
{
	enum class Classification
	{
		LAMBERTIAN = 0, METAL, DIELECTRIC, TOTAL
	};

	const char* TypeNames[(int)Classification::TOTAL] = { "Lambertian", "Metal", "Dielectric " };

	Classification Type = Classification::LAMBERTIAN;

	float Refractivendex = 1.5f;
	float Roughness = 1.0f;

	glm::vec3 Albedo{ 1.0f };
	glm::vec3 EmissionColor{ 1.0f };
	float EmissionPower = 0.0f;

	const glm::vec3 GetEmission() const { return EmissionColor * EmissionPower; }
};