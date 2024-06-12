#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "application.hpp"
#include "imgui_handler.hpp"
#include "camera.hpp"
#include "sphere.hpp"

Application::Application(std::string& title, int width, int height)
	: m_Width(width), m_Height(height)
{
	const char* glslVersion = "#version 130";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(m_Window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	ImGuiHandler::Init(glslVersion, m_Window);

	glm::vec3 cameraCenter(0.0f, 0.0f, 0.0f);
	m_Camera = &Camera::CreateInstance(m_Width, m_Height, cameraCenter);

	m_World.Add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5));
	m_World.Add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1), 100));
}

Application::~Application()
{
	ImGuiHandler::Terminate();

	std::cout << "Application: Terminated" << std::endl;

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

Application& Application::CreateInstance(std::string title, int width, int height)
{
	std::cout << "Application: Initialized" << std::endl;

	static Application s_Application(title, width, height);
	return s_Application;
}

void Application::MainLoop()
{
	if (!m_Window || !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return;

	unsigned int textureID;
	CreateTexture(textureID);

	while (!glfwWindowShouldClose(m_Window))
	{
		HandleInput();

		ImGuiID dockSpaceID;
		ImGuiHandler::BeginFrame(dockSpaceID);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Camera->Render(m_World);
		UpdateTexture(textureID);
		ImGuiHandler::DrawPixels(dockSpaceID, textureID);

		ImGuiHandler::EndFrame();

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Application::CreateTexture(unsigned int& textureID)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, m_Camera->ReadImageData().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::UpdateTexture(unsigned int& textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, m_Camera->ReadImageData().data());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::CallbackFramebufferResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Application::HandleInput()
{
	
}
