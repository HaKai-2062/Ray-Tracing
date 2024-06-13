#pragma once

#include <GLFW/glfw3.h>

#include "application.hpp"
#include "keycodes.hpp"

namespace Input
{
	bool IsKeyDown(KeyCode keycode)
	{
		GLFWwindow* windowHandle = Application::GetInstance().GetWindow();
		int state = glfwGetKey(windowHandle, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool IsMouseButtonDown(MouseButton button)
	{
		GLFWwindow* windowHandle = Application::GetInstance().GetWindow();
		int state = glfwGetMouseButton(windowHandle, (int)button);
		return state == GLFW_PRESS;
	}

	glm::vec2 GetMousePosition()
	{
		GLFWwindow* windowHandle = Application::GetInstance().GetWindow();

		double x, y;
		glfwGetCursorPos(windowHandle, &x, &y);
		return { (float)x, (float)y };
	}
}
