struct GLFWwindow;
class Renderer;

class Application
{
public:
	~Application();
	static Application& CreateInstance(std::string title, int width, int height);
	void MainLoop();
	void CallbackFramebufferResize(GLFWwindow* window, int width, int height);
	void HandleInput();

private:
	Application() = delete;
	Application(const Application&) = delete;
	Application(const Application&&) = delete;
	void operator=(const Application&) = delete;

	Application(std::string& title, int width, int height);
	void CreateTexture(unsigned int& textureID);
	void UpdateTexture(unsigned int& textureID);

private:
	GLFWwindow* m_Window = nullptr;
	Renderer* m_Renderer = nullptr;

	int m_Width = 0, m_Height = 0;
	unsigned int m_TextureID = 0;
};