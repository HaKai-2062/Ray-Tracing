#include "sphere.hpp"

bool Sphere::Hit(const Ray& ray, float rayXMin, float rayXMax, HitRecord& hitrecord) const
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
	if (root <= rayXMin || root >= rayXMax)
	{
		root = (h + sqrtDeterminant) / a;
		if (root <= rayXMin || root >= rayXMax)
		{
			return false;
		}
	}

	hitrecord.x = root;
	hitrecord.point = ray.At(root);
	hitrecord.normal = (hitrecord.point - m_Origin) / m_Radius;

	return true;
}