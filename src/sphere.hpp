#pragma once

#include "hittable.hpp"

class Sphere : public Hittable
{
public:
	Sphere(const glm::vec3& origin, float radius)
		: m_Origin(origin), m_Radius(radius) {}

	bool Hit(const Ray& ray, Interval rayInterval, HitRecord& hitrecord) const override;

private:
	glm::vec3 m_Origin;
	float m_Radius;
};