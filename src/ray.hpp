#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
	Ray(const glm::vec3& rayOrigin, const glm::vec3& rayDir)
		: m_RayOrigin(rayOrigin), m_RayDir(rayDir) {}
	
	const glm::vec3& GetOrigin() const	{ return m_RayOrigin; }
	const glm::vec3& GetDir() const { return m_RayDir; }
	glm::vec3 At(float x) const { return m_RayOrigin + x * m_RayDir; }

	glm::vec3 GetRayColor();

private:
	Ray() = delete;
	Ray(const Ray&) = delete;
	Ray(const Ray&&) = delete;
	void operator=(const Ray&) = delete;

private:
	glm::vec3 m_RayOrigin;
	glm::vec3 m_RayDir;
};