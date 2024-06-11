#include <glm/glm.hpp>

class Camera
{
public:

	static Camera& CreateInstance(glm::vec3& cameraCenter, float focalLength = 1.0f, float viewportHeight = 2.0f, float aspectRatio = 16.0f / 9, int imageWidth = 400);
	
	const glm::vec3& GetPixelTopLeft() const { return m_PixelTopLeft; }
	const glm::vec3& GetPixelDeltaU() const { return m_PixelDeltaU; }
	const glm::vec3& GetPixelDeltaV() const { return m_PixelDeltaV; }
	const glm::vec3& GetCameraCenter() const { return m_CameraCenter; }

private:
	~Camera();
	Camera(const Camera&) = delete;
	Camera(const Camera&&) = delete;
	void operator=(const Camera&) = delete;

	Camera(glm::vec3& cameraCenter, float focalLength, float viewportHeight, float aspectRatio, int imageWidth);

private:
	float m_AspectRatio, m_FocalLength, m_ViewportHeight, m_ViewportWidth;
	int m_ImageWidth, m_ImageHeight;
	glm::vec3 m_CameraCenter;

	glm::vec3 m_ViewportU;
	glm::vec3 m_ViewportV;
	glm::vec3 m_PixelDeltaU;
	glm::vec3 m_PixelDeltaV;
	glm::vec3 m_ViewportTopLeft;
	glm::vec3 m_PixelTopLeft;
};