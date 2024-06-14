#pragma once

struct GLFWwindow;
class Camera;

using ImGuiID = unsigned int;

namespace ImGuiHandler
{
	void Init(const char* glslVersion, GLFWwindow* window);
	void BeginFrame(ImGuiID& dockSpaceID, Camera* camera);
	void DrawPixels(ImGuiID& dockSpaceID, unsigned int textureID, int& viewportWidth, int& viewportHeight);
	void EndFrame();
	void Terminate();
}
