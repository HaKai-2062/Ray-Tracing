#pragma once

#include "ray.hpp"

struct HitRecord
{
public:
	glm::vec3 point;
	glm::vec3 normal;
	float x;
	bool frontFace;
};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, float rayXMin, float rayXMax, HitRecord& hitRecord) const = 0;
};