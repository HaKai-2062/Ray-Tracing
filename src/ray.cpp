#include "ray.hpp"
#include <iostream>

glm::vec3 Ray::GetRayColor()
{
	glm::vec3 normalDir = glm::normalize(m_RayDir);
	float a = 0.5f * (normalDir.y + 1.0f);
	return (1.0f - a) * glm::vec3(1.0f, 1.0f, 1.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f);;
}
