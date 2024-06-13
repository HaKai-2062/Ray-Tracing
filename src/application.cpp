#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "application.hpp"
#include "imgui_handler.hpp"
#include "camera.hpp"

Application* Application::s_Application;

Application::Application()
{
	const char* glslVersion = "#version 130";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(1280, 720, "RayTracing", NULL, NULL);
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

	std::cout << "Application: Initialized" << std::endl;

	ImGuiHandler::Init(glslVersion, m_Window);

	m_Camera = Camera::CreateInstance(45.0f, 0.1f, 100.0f);
}

Application::~Application()
{
	ImGuiHandler::Terminate();
	s_Application = nullptr;

	std::cout << "Application: Terminated" << std::endl;

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

Application& Application::GetInstance()
{
	if (s_Application != nullptr)
		return *s_Application;

	Application* application = new Application();
	s_Application = application;
	return *application;
}

void Application::MainLoop()
{
	if (!m_Window || !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return;

	unsigned int textureID;
	CreateTexture(textureID);

	float frameTime = (float)glfwGetTime();

	while (!glfwWindowShouldClose(m_Window))
	{
		m_Camera->OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Camera->OnUpdate((float)glfwGetTime() - frameTime);
		frameTime = (float)glfwGetTime();

		ImGuiID dockSpaceID;
		ImGuiHandler::BeginFrame(dockSpaceID);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		m_Camera->Render();
		UpdateTexture(textureID);
		ImGuiHandler::DrawPixels(dockSpaceID, textureID, m_ViewportWidth, m_ViewportHeight);

		ImGuiHandler::EndFrame();

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Application::CreateTexture(unsigned int& textureID)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ViewportWidth, m_ViewportHeight, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, m_Camera->ReadImageData().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::UpdateTexture(unsigned int& textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ViewportWidth, m_ViewportHeight, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, m_Camera->ReadImageData().data());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::CallbackFramebufferResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Application::HandleInput()
{
	
}
