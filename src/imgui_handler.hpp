#pragma once

struct GLFWwindow;

using ImGuiID = unsigned int;

namespace ImGuiHandler
{
	void Init(const char* glslVersion, GLFWwindow* window);
	void BeginFrame(ImGuiID& dockSpaceID);
	void DrawPixels(ImGuiID& dockSpaceID, unsigned int textureID);
	void EndFrame();
	void Terminate();
}
