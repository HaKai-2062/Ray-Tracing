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

Camera::Camera(float verticalFOV, float nearClip, float farClip)
	: m_VerticalFOV(verticalFOV), m_NearClip(nearClip), m_FarClip(farClip)
{
	m_ForwardDir = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Position = glm::vec3(0.0f, 0.0f, 3.0f);

	std::cout << "Camera: Initialized" << std::endl;
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
	Ray ray{};
	ray.Origin = m_Position;

	for (int y = 0; y < m_ViewportHeight; y++)
	{
		for (int x = 0; x < m_ViewportWidth; x++)
		{
			ray.Dir = m_RayDirs[x + y * m_ViewportWidth];
			glm::vec4 clampedRay = glm::clamp(TraceRay(ray), glm::vec4(0.0f), glm::vec4(1.0f));
			m_ImageData[x + y * m_ViewportWidth] = ConvertToRGBA(clampedRay);
		}
	}
}

glm::vec4 Camera::TraceRay(const Ray& ray)
{
	float radius = 0.5f;
	//rayDir = glm::normalize(rayDir);

	// (bx^2 + by^2)t^2 + 2(axbx +ayby)t + (ax^2 + ay^2 - r^2)
	// a = rayOrigin, b = rayDir, r = radius, t = hitDistance

	float a = glm::dot(ray.Dir, ray.Dir);
	float b = 2.0f * glm::dot(ray.Origin, ray.Dir);
	float c = glm::dot(ray.Origin, ray.Origin) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant < 0.0f)
		return { 0.0f, 0.0f, 0.0f, 1.0f };

	//float t0 = (-b + glm::sqrt(discriminant)) / (2 * a);
	float t1 = (-b - glm::sqrt(discriminant)) / (2.0f * a);

	//glm::vec3 h0 = rayOrigin + rayDir * t0;
	glm::vec3 hitPoint = ray.Origin + ray.Dir * t1;
	glm::vec3 sphereOrigin{ 0.0f };

	glm::vec3 normal = glm::normalize(hitPoint - sphereOrigin);
	glm::vec3 lightDir = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));

	float dot = glm::max(glm::dot(normal, -lightDir), 0.0f);

	glm::vec3 sphereColor{ 1.0f, 0.0f, 1.0f };
	sphereColor *= dot;
	return { sphereColor, 1.0f };
}