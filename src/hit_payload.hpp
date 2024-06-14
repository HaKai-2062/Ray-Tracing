#pragma once

struct HitPayload
{
	float HitDistance = -1.0f;
	glm::vec3 WorldPosition{ 0.0f };
	glm::vec3 WorldNormal{ 0.0f };

	int ObjectID = -1;
};
