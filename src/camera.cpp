#include <execution>

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

	/*
	{
		Material ground;
		ground.Albedo = glm::vec3(0.5f, 0.5f, 0.5f);
		ground.Type = Material::Classification::LAMBERTIAN;
		m_Material.push_back(ground);
	}
	{
		Sphere ground;
		ground.Origin = glm::vec3(0.0f, -1000.f, 0.0f);
		ground.Radius = 1000.0f;
		ground.MaterialIndex = (int)m_Material.size()-1;
		m_Sphere.push_back(ground);
	}

	{
		Material dielectric;
		dielectric.Refractivendex = 1.5f;
		dielectric.Type = Material::Classification::DIELECTRIC;
		m_Material.push_back(dielectric);
	}
	{
		Sphere dielectric;
		dielectric.Origin = glm::vec3(0.0f, 1.0f, 0.0f);
		dielectric.Radius = 1.0f;
		dielectric.MaterialIndex = (int)m_Material.size() - 1;
		m_Sphere.push_back(dielectric);
	}

	{
		Material lambertian;
		lambertian.Albedo = glm::vec3(0.4f, 0.2f, 0.1f);
		lambertian.Type = Material::Classification::LAMBERTIAN;
		m_Material.push_back(lambertian);
	}
	{
		Sphere lambertian;
		lambertian.Origin = glm::vec3(-4.0f, 1.0f, 0.0f);
		lambertian.Radius = 1.0f;
		lambertian.MaterialIndex = (int)m_Material.size() - 1;
		m_Sphere.push_back(lambertian);
	}

	{
		Material metal;
		metal.Albedo = glm::vec3(0.7f, 0.6f, 0.5f);
		metal.Roughness = 0.0f;
		metal.Type = Material::Classification::METAL;
		m_Material.push_back(metal);
	}
	{
		Sphere metal;
		metal.Origin = glm::vec3(4.0f, 1.0f, 0.0f);
		metal.Radius = 1.0f;
		metal.MaterialIndex = (int)m_Material.size() - 1;
		m_Sphere.push_back(metal);
	}

	for (int a = -8; a < 8; a+=2)
	{
		for (int b = -8; b < 8; b+=2)
		{
			float chosenMaterial = Utility::RandomFloat(0.0f, 1.0f);
			glm::vec3 origin(a + 0.9f * Utility::RandomFloat(0.0f, 1.0f), 0.2f, b + 0.9f * Utility::RandomFloat(0.0f, 1.0f));
			
			float length = glm::length(origin - glm::vec3(4.0f, 0.2f, 0.0f));

			if (length > 0.9f)
			{
				Material material;
				Sphere sphere;

				if (length < 3.0f)
				{
					material.Albedo = Utility::RandomVec3(0.0f, 1.0f);
					material.Type = Material::Classification::LAMBERTIAN;
					material.EmissionPower = 20.0;
					m_Material.push_back(material);

					sphere.Origin = origin;
					sphere.Radius = 0.2f;
					sphere.MaterialIndex = (int)m_Material.size() - 1;
					m_Sphere.push_back(sphere);
				}
				else if (chosenMaterial < 0.8f)
				{
					material.Albedo = Utility::RandomVec3(0.0f, 1.0f);
					material.Type = Material::Classification::LAMBERTIAN;
					m_Material.push_back(material);

					sphere.Origin = origin;
					sphere.Radius = 0.2f;
					sphere.MaterialIndex = (int)m_Material.size() - 1;
					m_Sphere.push_back(sphere);
				}
				else if (chosenMaterial < 0.95f)
				{
					material.Albedo = Utility::RandomVec3(0.5f, 1.0f);
					material.Roughness = Utility::RandomFloat(0.0f, 0.5f);
					material.Type = Material::Classification::METAL;
					m_Material.push_back(material);

					sphere.Origin = origin;
					sphere.Radius = 0.2f;
					sphere.MaterialIndex = (int)m_Material.size() - 1;
					m_Sphere.push_back(sphere);
				}
				else
				{
					material.Refractivendex = 1.5f;
					material.Type = Material::Classification::DIELECTRIC;
					m_Material.push_back(material);

					sphere.Origin = origin;
					sphere.Radius = 0.2f;
					sphere.MaterialIndex = (int)m_Material.size() - 1;
					m_Sphere.push_back(sphere);
				}
			}
		}
	}
	*/

	{
		Material material;
		material.Albedo = glm::vec3(0.9f, 0.9f, 0.9f);
		material.Roughness = 0.8f;
		m_Material.push_back(material);
	}

	{
		Material material;
		material.Albedo = glm::vec3(0.0f, 1.0f, 0.0f);
		material.Roughness = 0.1f;
		m_Material.push_back(material);
	}

	{
		Material material;
		material.Albedo = glm::vec3(0.8f, 0.3f, 0.1f);
		material.Roughness = 0.0f;
		material.EmissionColor = material.Albedo;
		material.EmissionPower = 20.0f;
		m_Material.push_back(material);
	}

	{
		Sphere sphere;

		sphere.Radius = 100.0f;
		sphere.Origin = glm::vec3(0.0f, -101.0f, 0.0f);
		sphere.MaterialIndex = 0;
		m_Sphere.push_back(sphere);
	}	
	
	{
		Sphere sphere;

		sphere.Radius = 1.0f;
		sphere.Origin = glm::vec3(0.0f, 0.0f, 0.0f);
		sphere.MaterialIndex = 1;
		m_Sphere.push_back(sphere);
	}

	{
		Sphere sphere;

		sphere.Radius = 1.0f;
		sphere.Origin = glm::vec3(3.0f, 3.0f, 0.0f);
		sphere.MaterialIndex = 2;
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
	delete[] m_ImageData;
	delete[] m_AccumulatedData;

	std::cout << "Camera: Terminated" << std::endl;
}

bool Camera::OnUpdate(float ts)
{
	glm::vec2 mousePos = Input::GetMousePosition();
	float mouseSensitivity = 0.002f;
	glm::vec2 mouseDelta = (mousePos - m_LastMousePosition) * mouseSensitivity;
	m_LastMousePosition = mousePos;
	GLFWwindow* windowHandle = Application::GetInstance().GetWindow();

	if (!Input::IsMouseButtonDown(MouseButton::Right))
	{
		glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)CursorMode::Normal);
		return false;
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

	return moved;
}

bool Camera::OnResize(uint32_t width, uint32_t height)
{
	if (width == m_ViewportWidth && height == m_ViewportHeight)
		return false;

	m_ViewportWidth = width;
	m_ViewportHeight = height;

	delete[] m_ImageData;
	m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];

	delete[] m_AccumulatedData;
	m_AccumulatedData = new glm::vec4[m_ViewportWidth * m_ViewportHeight];

	m_HorizontalIter.resize(m_ViewportWidth);
	m_VerticalIter.resize(m_ViewportHeight);

	for (uint32_t i = 0; i < m_ViewportWidth; i++)
		m_HorizontalIter[i] = i;
	for (uint32_t i = 0; i < m_ViewportHeight; i++)
		m_VerticalIter[i] = i;

	RecalculateProjection();
	RecalculateRayDirs();

	return true;
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
	if (m_FrameIndex == 1)
	{
		memset(m_AccumulatedData, 0, m_ViewportWidth * m_ViewportHeight * sizeof(glm::vec4));
	}

	if (m_MultiThreading)
	{
		std::for_each(std::execution::par, m_VerticalIter.begin(), m_VerticalIter.end(),
			[this](uint32_t y)
			{
				for (uint32_t x = 0; x < m_ViewportWidth; x++)
				{
					glm::vec4 color = RayGen(x, y);
					m_AccumulatedData[x + y * m_ViewportWidth] += color;
					
					glm::vec4 accumulatedColor = m_AccumulatedData[x + y * m_ViewportWidth];
					accumulatedColor /= (float)m_FrameIndex;

					accumulatedColor = glm::clamp(accumulatedColor, glm::vec4(0.0f), glm::vec4(1.0f));
					m_ImageData[x + y * m_ViewportWidth] = Utility::ConvertToRGBA(accumulatedColor);
				}
			});
	}
	else
	{
		for (uint32_t y = 0; y < m_ViewportHeight; y++)
		{
			for (uint32_t x = 0; x < m_ViewportWidth; x++)
			{
				glm::vec4 color = RayGen(x, y);
				m_AccumulatedData[x + y * m_ViewportWidth] += color;

				glm::vec4 accumulatedColor = m_AccumulatedData[x + y * m_ViewportWidth];
				accumulatedColor /= (float)m_FrameIndex;

				accumulatedColor = glm::clamp(accumulatedColor, glm::vec4(0.0f), glm::vec4(1.0f));
				m_ImageData[x + y * m_ViewportWidth] = Utility::ConvertToRGBA(accumulatedColor);
			}
		}
	}

	if (m_Accumulate)
	{
		m_FrameIndex++;
	}
	else
	{
		ResetFrameIndex();
	}
}

glm::vec4 Camera::RayGen(int x, int y)
{
	Ray ray{};
	ray.Origin = m_Position;
	ray.Dir = m_RayDirs[x + y * m_ViewportWidth];
	
	glm::vec3 light{ 0.0f };
	glm::vec3 contribution{ 1.0f };

	int bounces = 10;
	for (int i = 0; i < bounces; i++)
	{
		HitPayload payload = ray.TraceRay(m_Sphere);
		
		if (payload.HitDistance < 0.0f)
		{
			light += m_SkyColor * contribution;
			break;
		}

		const Sphere& sphere = m_Sphere[payload.ObjectID];
		const Material& material = m_Material[sphere.MaterialIndex];

		contribution *= material.Albedo;
		light += material.GetEmission() * contribution;

		// Avoiding self intersection
		ray.Origin = payload.WorldPosition + payload.WorldNormal * 0.001f;

		switch (material.Type)
		{
		case Material::Classification::LAMBERTIAN:
		{
			ray.Dir = payload.WorldNormal + glm::normalize(Utility::RandomInUnitSphere());

			// If world normal and randDir become opposite rayDir becomes zero so we make a check for it
			float tolerance = 0.0001f;
			if (std::fabs(ray.Dir[0]) < tolerance && std::fabs(ray.Dir[1]) < tolerance && std::fabs(ray.Dir[2]) < tolerance)
				ray.Dir = payload.WorldNormal;

			break;
		}

		case Material::Classification::METAL:
		{
			ray.Dir = glm::reflect(ray.Dir, payload.WorldNormal);

			// Fuzziness or Roughness
			ray.Dir = glm::normalize(ray.Dir) + (material.Roughness * glm::normalize(Utility::RandomInUnitSphere()));

			bool innerFace = glm::dot(ray.Dir, payload.WorldNormal) < 0;

			// To prevent ray from going inside the sphere
			if (innerFace)
				light = glm::vec3(0.0f, 0.0f, 0.0f);

			break;
		}

		case Material::Classification::DIELECTRIC:
		{
			float eta = material.Refractivendex;
			float cosi = glm::dot(ray.Dir, payload.WorldNormal);
			float etai = 1.0f, etat = eta;
			if (cosi > 0) { std::swap(etai, etat); }
			float etaRatio = etai / etat;

			glm::vec3 refractedDir = glm::refract(ray.Dir, payload.WorldNormal, etaRatio);
			float fresnelReflectance = Utility::FresnelSchlick(std::fabs(cosi), eta);

			if (glm::length(refractedDir) > 0)
			{
				// Both reflection and refraction happen
				glm::vec3 reflectedDir = glm::reflect(ray.Dir, payload.WorldNormal);

				// Choose either reflection or refraction based on Fresnel term
				if (Utility::RandomFloat(0.0f, 1.0f) < fresnelReflectance)
				{
					ray.Dir = reflectedDir;
				}
				else
				{
					ray.Dir = refractedDir;
					ray.Origin = payload.WorldPosition + refractedDir * 0.001f;
				}
			}
			else
			{
				// Total internal reflection
				ray.Dir = glm::reflect(ray.Dir, payload.WorldNormal);
			}

			break;
		}
		}
	}
	
	return { light, 1.0f };
}