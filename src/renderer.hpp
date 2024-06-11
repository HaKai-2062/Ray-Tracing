#pragma once

#include <vector>

#include <glm/glm.hpp>

class Camera;

class Renderer
{
public:
	~Renderer();
	static Renderer& CreateInstance(int width, int height);
	void UpdateDimensions(int width, int height);
	void SetPixelData();
	const std::vector<glm::vec3>& ReadPixelData() const;

public:
	int m_Width = 0 , m_Height = 0;

private:
	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer(const Renderer&&) = delete;
	void operator=(const Renderer&) = delete;

	Renderer(int width, int height);

private:
	std::vector<glm::vec3> m_ColorData;
	Camera* m_Camera = nullptr;
};