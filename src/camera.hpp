#pragma once

#include <glm/glm.hpp>
#include "hittable.hpp"

class Ray;

class Camera
{
public:
	static Camera& CreateInstance(int width, int height, glm::vec3& cameraCenter, float focalLength = 1.0f, float viewportHeight = 2.0f);
	void Render(const Hittable& world);
	glm::vec3 PerPixel(const glm::vec2 coord);
	const std::vector<glm::vec3>& ReadImageData() const { return m_ImageData; }

private:
	~Camera();
	Camera(const Camera&) = delete;
	Camera(const Camera&&) = delete;
	void operator=(const Camera&) = delete;

	Camera(int width, int height, glm::vec3& cameraCenter, float focalLength, float viewportHeight);

private:
	float m_AspectRatio, m_FocalLength, m_ViewportHeight, m_ViewportWidth;
	int m_ImageWidth, m_ImageHeight;
	int m_MaxBounces, m_MaxSamples;
	std::vector<glm::vec3> m_ImageData;

	glm::vec3 m_CameraCenter;
	glm::vec3 m_ViewportU;
	glm::vec3 m_ViewportV;
	glm::vec3 m_PixelDeltaU;
	glm::vec3 m_PixelDeltaV;
	glm::vec3 m_ViewportTopLeft;
	glm::vec3 m_PixelTopLeft;
};