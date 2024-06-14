#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "camera.hpp"
#include "input.hpp"
#include "ray.hpp"
#include "utility.hpp"
#include "sphere.hpp"
#include "hit_payload.hpp"
#include "material.hpp"

Camera::Camera(float verticalFOV, float nearClip, float farClip)
	: m_VerticalFOV(verticalFOV), m_NearClip(nearClip), m_FarClip(farClip)
{
	m_ForwardDir = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Position = glm::vec3(0.0f, 0.0f, 6.0f);

	std::cout << "Camera: Initialized" << std::endl;

	{
		Material material;
		material.Albedo = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Material.push_back(material);
	}

	{
		Material material;
		material.Albedo = glm::vec3(1.0f, 0.0f, 1.0f);
		m_Material.push_back(material);
	}

	{
		Sphere sphere;

		sphere.Radius = 1.0f;
		sphere.Origin = glm::vec3(0.0f, 0.0f, 0.0f);
		sphere.MaterialIndex = 0;
		m_Sphere.push_back(sphere);
	}

	{
		Sphere sphere;

		sphere.Radius = 100.0f;
		sphere.Origin = glm::vec3(0.0f, -101.0f, 0.0f);
		sphere.MaterialIndex = 1;
		m_Sphere.push_back(sphere);
	}
}

Camera* Camera::CreateInstance(float verticalFOV, float nearClip, float farClip)
{
	static Camera camera(verticalFOV, nearClip, farClip);
	return &camera;
}

Camera::~Camera()
{
	std::cout << "Camera: Terminated" << std::endl;
}

void Camera::OnUpdate(float ts)
{
	glm::vec2 mousePos = Input::GetMousePosition();
	float mouseSensitivity = 0.002f;
	glm::vec2 mouseDelta = (mousePos - m_LastMousePosition) * mouseSensitivity;
	m_LastMousePosition = mousePos;
	GLFWwindow* windowHandle = Application::GetInstance().GetWindow();

	if (!Input::IsMouseButtonDown(MouseButton::Right))
	{
		glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)CursorMode::Normal);
		return;
	}

	glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)CursorMode::Locked);

	bool moved = false;
	constexpr glm::vec3 upDir(0.0f, 1.0f, 0.0f);
	glm::vec3 rightDir = glm::cross(m_ForwardDir, upDir);

	float speed = 5.0f;

	if (Input::IsKeyDown(KeyCode::W))
	{
		m_Position += m_ForwardDir * speed * ts;
		moved = true;
	}

	else if (Input::IsKeyDown(KeyCode::S))
	{
		m_Position -= m_ForwardDir * speed * ts;
		moved = true;
	}

	if (Input::IsKeyDown(KeyCode::D))
	{
		m_Position += rightDir * speed * ts;
		moved = true;
	}
	else if (Input::IsKeyDown(KeyCode::A))
	{
		m_Position -= rightDir * speed * ts;
		moved = true;
	}

	if (Input::IsKeyDown(KeyCode::Q))
	{
		m_Position -= upDir * speed * ts;
		moved = true;
	}
	else if (Input::IsKeyDown(KeyCode::E))
	{
		m_Position += upDir * speed * ts;
		moved = true;
	}

	// Rotation
	if (mouseDelta.x != 0.0f || mouseDelta.y != 0.0f)
	{
		float pitchDelta = mouseDelta.y * m_RotationSpeed;
		float yawDelta = mouseDelta.x * m_RotationSpeed;

		glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDir),
			glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));
		
		m_ForwardDir = glm::rotate(q, m_ForwardDir);

		moved = true;
	}

	if (moved)
	{
		RecalculateView();
		RecalculateRayDirs();
	}
}

void Camera::OnResize(uint32_t width, uint32_t height)
{
	if (width == m_ViewportWidth && height == m_ViewportHeight)
		return;

	m_ViewportWidth = width;
	m_ViewportHeight = height;

	m_ImageData.clear();
	m_ImageData.resize(m_ViewportWidth * m_ViewportHeight);

	RecalculateProjection();
	RecalculateRayDirs();
}

void Camera::RecalculateProjection()
{
	m_Projection = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearClip, m_FarClip);
	m_InverseProjection = glm::inverse(m_Projection);
}

void Camera::RecalculateView()
{
	m_View = glm::lookAt(m_Position, m_Position + m_ForwardDir, glm::vec3(0.0f, 1.0f, 0.0f));
	m_InverseView = glm::inverse(m_View);
}

void Camera::RecalculateRayDirs()
{
	m_RayDirs.resize(m_ViewportWidth * m_ViewportHeight);

	for (uint32_t y = 0; y < m_ViewportHeight; y++)
	{
		for (uint32_t x = 0; x < m_ViewportWidth; x++)
		{
			glm::vec2 coord = { (float)x / m_ViewportWidth, (float)y / m_ViewportHeight };
			coord = coord * 2.0f - 1.0f;	// -1 -> 1

			glm::vec4 target = m_InverseProjection * glm::vec4(coord.x, coord.y, 1.0f, 1.0f);
			glm::vec3 rayDir = glm::vec3(m_InverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0.0f));	//NDC to WorldSpace
			m_RayDirs[x + y * m_ViewportWidth] = rayDir;
		}
	}
}

void Camera::Render()
{
	for (int y = 0; y < m_ViewportHeight; y++)
	{
		for (int x = 0; x < m_ViewportWidth; x++)
		{
			glm::vec4 clampedRay = glm::clamp(RayGen(x, y), glm::vec4(0.0f), glm::vec4(1.0f));
			m_ImageData[x + y * m_ViewportWidth] = ConvertToRGBA(clampedRay);
		}
	}
}

glm::vec4 Camera::RayGen(int x, int y)
{
	Ray ray{};
	ray.Origin = m_Position;
	ray.Dir = m_RayDirs[x + y * m_ViewportWidth];
	glm::vec3 color{ 0.0f };
	float multiplier = 1.0f;

	int bounces = 2;
	for (int i = 0; i < bounces; i++)
	{
		HitPayload payload = ray.TraceRay(m_Sphere);

		if (payload.HitDistance < 0.0f)
		{
			glm::vec3 skyColor{ 0.0f, 0.0f, 0.0f };
			color += skyColor;
			break;
		}

		glm::vec3 lightDir = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));
		float lightIntensity = glm::max(glm::dot(payload.WorldNormal, -lightDir), 0.0f);

		Sphere sphere = m_Sphere[payload.ObjectID];
		glm::vec3 sphereColor = m_Material[sphere.MaterialIndex].Albedo;
		sphereColor *= lightIntensity;
		color += sphereColor;

		multiplier *= 0.7f;
		ray.Origin = payload.WorldPosition + payload.WorldNormal * 0.001f;
		ray.Dir = glm::reflect(ray.Dir, payload.WorldNormal);
	}

	return {color, 1.0f};
}