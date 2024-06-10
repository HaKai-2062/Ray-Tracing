#include <iostream>

#include <renderer.hpp>

Renderer::Renderer(int width, int height)
	: m_Width(width), m_Height(height)
{
	m_ColorData.reserve(m_Width * m_Height);

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
	m_ColorData.clear();

	for (int i = 0; i < m_Height; i++)
	{
		for (int j = 0; j < m_Width; j++)
		{
			float r = float(j) / (m_Width - 1);
			float g = float(i) / (m_Height - 1);

			m_ColorData.emplace_back(r, g, 0.0f, 1.0f);
		}
	}
}

const std::vector<Color>& Renderer::ReadPixelData() const
{
	return m_ColorData;
}