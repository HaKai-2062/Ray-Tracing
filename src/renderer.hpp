#include <vector>

struct Color
{
	float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;
};

class Renderer
{
public:
	~Renderer();
	static Renderer& CreateInstance(int width, int height);
	void UpdateDimensions(int width, int height);
	void SetPixelData();
	const std::vector<Color>& ReadPixelData() const;

public:
	int m_Width = 0 , m_Height = 0;

private:
	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer(const Renderer&&) = delete;
	void operator=(const Renderer&) = delete;

	Renderer(int width, int height);

private:
	std::vector<Color> m_ColorData;
};