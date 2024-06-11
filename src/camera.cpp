#include <iostream>

#include "camera.hpp"

Camera::Camera(glm::vec3& cameraCenter, float focalLength, float viewportHeight)
	: m_CameraCenter(cameraCenter), m_FocalLength(focalLength), m_ViewportHeight(viewportHeight)
{
	m_ImageWidth = 1280;
	m_ImageHeight = 720;
	m_AspectRatio = float(1280) / 720;

	m_ViewportWidth = m_ViewportHeight * (float(m_ImageWidth) / m_ImageHeight);
	
	m_ViewportU = glm::vec3(m_ViewportWidth, 0.0f, 0.0f);
	m_ViewportV = glm::vec3(0.0f, -m_ViewportHeight, 0.0f);

	m_PixelDeltaU = m_ViewportU / float(m_ImageWidth);
	m_PixelDeltaV = m_ViewportV / float(m_ImageHeight);

	m_ViewportTopLeft = m_CameraCenter - glm::vec3(0.0f, 0.0f, m_FocalLength) - m_ViewportU / 2.0f - m_ViewportV / 2.0f;
	m_PixelTopLeft = m_ViewportTopLeft + 0.5f * (m_PixelDeltaU + m_PixelDeltaV);

	std::cout << "Camera: Initialized" << std::endl;
}

Camera& Camera::CreateInstance(glm::vec3& cameraCenter, float focalLength, float viewportHeight)
{
	static Camera camera(cameraCenter, focalLength, viewportHeight);
	return camera;
}

Camera::~Camera()
{
	std::cout << "Camera: Terminated" << std::endl;
}
