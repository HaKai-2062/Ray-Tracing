#include "sphere.hpp"

bool Sphere::Hit(const Ray& ray, Interval rayInterval, HitRecord& hitrecord) const
{
	glm::vec3 oc = m_Origin - ray.GetOrigin();
	float a = glm::dot(ray.GetDir(), ray.GetDir());
	float h = glm::dot(ray.GetDir(), oc);
	float c = glm::dot(oc, oc) - m_Radius * m_Radius;

	float discriminant = h * h - a * c;
	if (discriminant < 0)
	{
		return false;
	}

	float sqrtDeterminant = glm::sqrt(discriminant);
	float root = (h - sqrtDeterminant) / a;
	if (!rayInterval.Surrounds(root))
	{
		root = (h + sqrtDeterminant) / a;
		if (!rayInterval.Surrounds(root))
		{
			return false;
		}
	}

	hitrecord.x = root;
	hitrecord.point = ray.At(root);
	glm::vec3 outNormal = (hitrecord.point - m_Origin) / m_Radius;
	hitrecord.frontFace = dot(ray.GetDir(), outNormal) < 0;
	hitrecord.normal = hitrecord.frontFace ? outNormal : -outNormal;

	return true;
}