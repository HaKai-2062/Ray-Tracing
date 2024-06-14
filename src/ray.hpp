#pragma once

#include <glm/glm.hpp>
#include <vector>

struct HitPayload;

class Ray
{
public:
	Ray() = default;
	HitPayload TraceRay(const std::vector<Shape*>& m_Shapes);
	HitPayload ClosestHit(const std::vector<Shape*>& m_Shapes, float hitDistance, int objectID);
	HitPayload Miss();

public:
	glm::vec3 Origin;
	glm::vec3 Dir;
};