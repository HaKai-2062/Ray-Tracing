#pragma once

#include <glm/glm.hpp>
#include <vector>

struct HitPayload;

class Ray
{
public:
	Ray() = default;
	HitPayload TraceRay(const std::vector<Sphere>& spheres) const;
	HitPayload ClosestHit(const std::vector<Sphere>& spheres, float hitDistance, int objectID) const;
	HitPayload Miss() const;

public:
	glm::vec3 Origin;
	glm::vec3 Dir;
};