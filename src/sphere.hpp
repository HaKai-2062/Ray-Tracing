#pragma once

#include <glm/glm.hpp>

#include "shape.hpp"

class Sphere : public Shape
{
public:
	float Radius = 0.5f;
	glm::vec3 Origin{ 0.0f };
	glm::vec3 Albedo{ 0.7f };
};