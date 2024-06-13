#pragma once

struct GLFWwindow;
class Camera;

class Application
{
public:
	~Application();
	static Application& GetInstance();
	GLFWwindow* GetWindow() const{ return m_Window; }

	void MainLoop();
	void CallbackFramebufferResize(GLFWwindow* window, int width, int height);
	void HandleInput();

private:
	Application();
	Application(const Application&) = delete;
	Application(const Application&&) = delete;
	void operator=(const Application&) = delete;
	void CreateTexture(unsigned int& textureID);
	void UpdateTexture(unsigned int& textureID);

private:
	GLFWwindow* m_Window = nullptr;
	Camera* m_Camera = nullptr;

	int m_Width = 0, m_Height = 0, m_ViewportWidth = 0, m_ViewportHeight = 0;
	unsigned int m_TextureID = 0;

	static Application* s_Application;
};