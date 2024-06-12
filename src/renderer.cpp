#include <iostream>

#include "renderer.hpp"
#include "camera.hpp"
#include "ray.hpp"
#include "sphere.hpp"

Renderer::Renderer(int width, int height)
	: m_Width(width), m_Height(height)
{
	m_ColorData.reserve(m_Width * m_Height);

	glm::vec3 cameraCenter({ 0.0f, 0.0f, 0.0f });
	m_Camera = &Camera::CreateInstance(cameraCenter);

	std::cout << "Renderer: Initialized" << std::endl;
}

Renderer& Renderer::CreateInstance(int width, int height)
{
	static Renderer renderer(width, height);
	return renderer;
}

Renderer::~Renderer()
{
	std::cout << "Renderer: Terminated" << std::endl;
}

void Renderer::UpdateDimensions(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

void Renderer::SetPixelData()
{
	//m_ColorData.clear();
	Sphere sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);

	for (int j = 0; j < m_Height; j++)
	{
		for (int i = 0; i < m_Width; i++)
		{
			glm::vec3 pixelCenter = m_Camera->GetPixelTopLeft() + (float(i) * m_Camera->GetPixelDeltaU()) + (float(j) * m_Camera->GetPixelDeltaV());
			glm::vec3 rayDir = pixelCenter - m_Camera->GetCameraCenter();
			Ray ray(m_Camera->GetCameraCenter(), rayDir);
			
			glm::vec3 rayColor;
			HitRecord hitRecord;
			bool isHit = sphere.Hit(ray, 0.0f, 1.0f, hitRecord);
			if (isHit)
			{
				glm::vec3 normal = glm::normalize(ray.At(hitRecord.x) - glm::vec3(0.0f, 0.0f, -1.0f));
				rayColor = 0.5f * (1.0f + normal);
			}
			else
			{
				rayColor = ray.GetRayColor();
			}
			
			m_ColorData[i + j * m_Width] = rayColor;
		}
	}
}

const std::vector<glm::vec3>& Renderer::ReadPixelData() const
{
	return m_ColorData;
}
