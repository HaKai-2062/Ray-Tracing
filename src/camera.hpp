#pragma once

#include <glm/glm.hpp>

class Ray;
struct Sphere;
struct Material;

class Camera
{
public:
	static Camera* CreateInstance(float verticalFOV, float nearClip, float farClip);
	void OnUpdate(float ts);
	void OnResize(uint32_t width, uint32_t height);

	// Renderer specific
	void Render();
	const std::vector<uint32_t>& ReadImageData() const { return m_ImageData; }

private:
	~Camera();
	Camera(const Camera&) = delete;
	Camera(const Camera&&) = delete;
	void operator=(const Camera&) = delete;

	Camera(float verticalFOV, float nearClip, float farClip);
	void RecalculateProjection();
	void RecalculateView();
	void RecalculateRayDirs();

	// Renderer specific
	glm::vec4 RayGen(int x, int y);

public:
	// Controlled by ImGui
	std::vector<Sphere> m_Sphere;
	std::vector<Material> m_Material;

private:
	std::vector<uint32_t> m_ImageData;

	glm::mat4 m_Projection{ 1.0f };
	glm::mat4 m_View{ 1.0f };
	glm::mat4 m_InverseProjection{ 1.0f };
	glm::mat4 m_InverseView{ 1.0f };

	float m_VerticalFOV = 45.0f;
	float m_NearClip = 0.1f;
	float m_FarClip = 100.0f;

	float m_RotationSpeed = 0.3f;

	glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_ForwardDir{ 0.0f, 0.0f, 0.0f };

	// Cached ray directions
	std::vector<glm::vec3> m_RayDirs;

	glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };

	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
};