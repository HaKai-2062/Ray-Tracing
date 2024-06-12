#include <iostream>

#include "camera.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittable_list.hpp"

Camera::Camera(int width, int height, glm::vec3& cameraCenter, float focalLength, float viewportHeight)
	: m_ImageWidth(width), m_ImageHeight(height), m_CameraCenter(cameraCenter), m_FocalLength(focalLength), m_ViewportHeight(viewportHeight)
{
	m_AspectRatio = m_ImageWidth / m_ImageHeight;

	m_ViewportWidth = m_ViewportHeight * (float(m_ImageWidth) / m_ImageHeight);
	
	m_ViewportU = glm::vec3(m_ViewportWidth, 0.0f, 0.0f);
	m_ViewportV = glm::vec3(0.0f, -m_ViewportHeight, 0.0f);

	m_PixelDeltaU = m_ViewportU / float(m_ImageWidth);
	m_PixelDeltaV = m_ViewportV / float(m_ImageHeight);

	m_ViewportTopLeft = m_CameraCenter - glm::vec3(0.0f, 0.0f, m_FocalLength) - m_ViewportU / 2.0f - m_ViewportV / 2.0f;
	m_PixelTopLeft = m_ViewportTopLeft + 0.5f * (m_PixelDeltaU + m_PixelDeltaV);

	m_ImageData.reserve(m_ImageWidth * m_ImageHeight);


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
	for (int j = 0; j < m_ImageHeight; j++)
	{
		for (int i = 0; i < m_ImageWidth; i++)
		{
			glm::vec3 pixelCenter = m_PixelTopLeft + (float(i) * m_PixelDeltaU) + (float(j) * m_PixelDeltaV);
			glm::vec3 rayDir = pixelCenter - m_CameraCenter;
			Ray ray(m_CameraCenter, rayDir);
			
			glm::vec3 rayColor;
			HitRecord hitRecord;
			bool isHit = world.Hit(ray, Interval(0.0f, std::numeric_limits<float>::max()), hitRecord);
			if (isHit)
			{
				rayColor = 0.5f * (1.0f + hitRecord.normal);
			}
			else
			{
				rayColor = ray.GetRayColor();
			}
			
			m_ImageData[i + j * m_ImageWidth] = rayColor;
		}
	}
}
