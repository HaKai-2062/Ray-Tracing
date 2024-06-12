#pragma once

#include <glm/glm.hpp>
#include "hittable.hpp"

class Ray;

class Camera
{
public:
	static Camera& CreateInstance(int width, int height, glm::vec3& cameraCenter, float focalLength = 1.0f, float viewportHeight = 2.0f);
	void Render(const Hittable& world);
	const std::vector<glm::vec3>& ReadImageData() const { return m_ImageData; }

private:
	~Camera();
	Camera(const Camera&) = delete;
	Camera(const Camera&&) = delete;
	void operator=(const Camera&) = delete;

	Camera(int width, int height, glm::vec3& cameraCenter, float focalLength, float viewportHeight);
	glm::vec3& GetRayColor(const Ray& ray, const Hittable& hittable) const;

private:
	float m_AspectRatio, m_FocalLength, m_ViewportHeight, m_ViewportWidth;
	int m_ImageWidth, m_ImageHeight;
	std::vector<glm::vec3> m_ImageData;

	glm::vec3 m_CameraCenter;
	glm::vec3 m_ViewportU;
	glm::vec3 m_ViewportV;
	glm::vec3 m_PixelDeltaU;
	glm::vec3 m_PixelDeltaV;
	glm::vec3 m_ViewportTopLeft;
	glm::vec3 m_PixelTopLeft;
};