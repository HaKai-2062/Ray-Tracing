#include "sphere.hpp"
#include "ray.hpp"
#include "hit_payload.hpp"

HitPayload Ray::TraceRay(const std::vector<Sphere>& spheres) const
{
	float closestT = std::numeric_limits<float>::max();
	int closestSphere = -1;

	for (int i = 0; i < spheres.size(); i++)
	{
		Sphere sphere = spheres[i];

		glm::vec3 origin = Origin - sphere.Origin;
		//rayDir = glm::normalize(rayDir);

		float a = glm::dot(Dir, Dir);
		float b = 2.0f * glm::dot(origin, Dir);
		float c = glm::dot(origin, origin) - sphere.Radius * sphere.Radius;

		float discriminant = b * b - 4.0f * a * c;

		if (discriminant < 0.0f)
		{
			continue;
		}

		//float t0 = (-b + glm::sqrt(discriminant)) / (2 * a);
		float t1 = (-b - glm::sqrt(discriminant)) / (2.0f * a);

		if (t1 > 0.0f && t1 < closestT)
		{
			closestT = t1;
			closestSphere = i;
		}
	}

	if (closestSphere == -1)
	{
		return Miss();
	}

	return ClosestHit(spheres, closestT, closestSphere);
}

HitPayload Ray::ClosestHit(const std::vector<Sphere>& spheres, float hitDistance, int objectID) const
{
	HitPayload payload;
	payload.HitDistance = hitDistance;
	payload.ObjectID = objectID;

	Sphere sphere = spheres[objectID];

	glm::vec3 origin = Origin - sphere.Origin;

	//glm::vec3 h0 = rayOrigin + rayDir * t0;
	payload.WorldPosition = origin + Dir * hitDistance;
	payload.WorldNormal = glm::normalize(payload.WorldPosition);

	// This is done because we subtracted origin of shape to draw it away from 0,0
	payload.WorldPosition += sphere.Origin;

	return payload;
}

HitPayload Ray::Miss() const
{
	HitPayload payload;
	return payload;
}