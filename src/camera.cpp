#include <iostream>

#include "camera.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittable_list.hpp"

static glm::vec3 rayColor(const Ray& ray, int maxBounces, const Hittable& world);

Camera::Camera(int width, int height, glm::vec3& cameraCenter, float focalLength, float viewportHeight)
	: m_ImageWidth(width), m_ImageHeight(height), m_CameraCenter(cameraCenter), m_FocalLength(focalLength), m_ViewportHeight(viewportHeight)
{
	m_AspectRatio = float(m_ImageWidth) / m_ImageHeight;

	m_ViewportWidth = m_ViewportHeight * (float(m_ImageWidth) / m_ImageHeight);
	
	m_ViewportU = glm::vec3(m_ViewportWidth, 0.0f, 0.0f);
	m_ViewportV = glm::vec3(0.0f, -m_ViewportHeight, 0.0f);

	m_PixelDeltaU = m_ViewportU / float(m_ImageWidth);
	m_PixelDeltaV = m_ViewportV / float(m_ImageHeight);

	m_ViewportTopLeft = m_CameraCenter - glm::vec3(0.0f, 0.0f, m_FocalLength) - m_ViewportU / 2.0f - m_ViewportV / 2.0f;
	m_PixelTopLeft = m_ViewportTopLeft + 0.5f * (m_PixelDeltaU + m_PixelDeltaV);

	m_ImageData.reserve(m_ImageWidth * m_ImageHeight);

	m_MaxBounces = 10;
	m_MaxSamples = 10;

	std::cout << "Camera: Initialized" << std::endl;
}

Camera& Camera::CreateInstance(int width, int height, glm::vec3& cameraCenter, float focalLength, float viewportHeight)
{
	static Camera camera(width, height, cameraCenter, focalLength, viewportHeight);
	return camera;
}

Camera::~Camera()
{
	std::cout << "Camera: Terminated" << std::endl;
}

void Camera::Render(const Hittable& world) 
{
	for (int y = 0; y < m_ImageHeight; y++)
	{
		for (int x = 0; x < m_ImageWidth; x++)
		{
			glm::vec3 pixelCenter = m_PixelTopLeft + (float(x) * m_PixelDeltaU) + (float(y) * m_PixelDeltaV);
			glm::vec3 rayDir = pixelCenter - m_CameraCenter;
			Ray ray(m_CameraCenter, rayDir);
			
			glm::vec3 color = rayColor(ray, m_MaxBounces, world);

			m_ImageData[x + y * m_ImageWidth] = color; 
		}
	}
}

static glm::vec3 rayColor(const Ray& ray, int maxBounces, const Hittable& world)
{
	if (maxBounces <= 0)
		return glm::vec3(0.0f, 0.0f, 0.0f);

	HitRecord hitRecord;
	bool isHit = world.Hit(ray, Interval(0.001f, std::numeric_limits<float>::infinity()), hitRecord);
	if (isHit)
	{
		glm::vec3 direction = randOnHemisphere(hitRecord.normal);
		return 0.5f * rayColor(Ray(hitRecord.point, direction), maxBounces-1, world);
	}
	
	glm::vec3 normalDir = glm::normalize(ray.GetDir());
	float a = 0.5f * (normalDir.y + 1.0f);
	return (1.0f - a) * glm::vec3(1.0f, 1.0f, 1.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f);
}
