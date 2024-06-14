#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "imgui_handler.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "material.hpp"

void ImGuiHandler::Init(const char* glslVersion, GLFWwindow* window)
{
    std::cout << "ImGui: Initialized" << std::endl;

    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    // Dockspace setup
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;
}

void ImGuiHandler::BeginFrame(ImGuiID& dockSpaceID, Camera* camera)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    dockSpaceID = ImGui::DockSpaceOverViewport(0U, ImGui::GetMainViewport(), ImGuiDockNodeFlags_HiddenTabBar);

    ImGui::Begin("Main");
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Frame delay: %.3f ms", 1000.0f / io.Framerate);
    ImGui::Text("Frames per second: %.1f", io.Framerate);
    ImGui::End();

    ImGui::Begin("World");
    
    std::vector<Sphere>& spheres = camera->m_Sphere;
    std::vector<Material>& materials = camera->m_Material;

    if (ImGui::Button("Reset"))
    {
        camera->ResetFrameIndex();
    }

    ImGui::Checkbox("Accumulate", &camera->m_Accumulate);
    ImGui::Checkbox("MultiThreading", &camera->m_MultiThreading);

    ImGui::Text("Sky Color");
    ImGui::Separator();
    ImGui::ColorEdit3("Sky", glm::value_ptr(camera->m_SkyColor));
    ImGui::NewLine();

    ImGui::Text("Spheres");
    ImGui::Separator();
    for (int i = 0; i < spheres.size(); i++)
    {
        ImGui::PushID(i);

        Sphere& sphere = spheres[i];
        ImGui::DragFloat3("Position", glm::value_ptr(sphere.Origin), 0.1f);
        ImGui::DragFloat("Radius", &sphere.Radius, 0.1f);
        ImGui::DragInt("MaterailID", &sphere.MaterialIndex, 0.1f, 0, static_cast<int>(materials.size()) - 1);

        ImGui::NewLine();
        ImGui::PopID();
    }

    ImGui::NewLine();
    ImGui::Text("Materials");
    ImGui::Separator();

    for (int i = 0; i < materials.size(); i++)
    {
        ImGui::PushID(i);

        Material& material = materials[i];
        ImGui::ColorEdit3("Albedo", glm::value_ptr(material.Albedo));
        ImGui::DragFloat("Roughness", &material.Roughness, 0.001f, 0.0f, 1.0f);
        ImGui::DragFloat("Metallic", &material.Metallic, 0.001f, 0.0f, 1.0f);

        ImGui::NewLine();
        ImGui::PopID();
    }

    ImGui::End();
}

void ImGuiHandler::DrawPixels(ImGuiID& dockSpaceID, unsigned int textureID, int& viewportWidth, int& viewportHeight)
{
    ImGui::SetNextWindowDockID(dockSpaceID, ImGuiCond_FirstUseEver);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0.f, 0.f));
    bool open = false;
    ImGui::Begin("SceneWindow", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_HorizontalScrollbar);
    ImVec2 getRegion = ImGui::GetContentRegionAvail();

    viewportWidth = static_cast<int>(getRegion.x);
    viewportHeight = static_cast<int>(getRegion.y);

    // To invert the image
    ImGui::Image((void*)(unsigned int)(textureID), getRegion, ImVec2(0, 1), ImVec2(1, 0));
    //ImGui::Image((void*)(unsigned int)(textureID), getRegion);
    ImGui::PopStyleVar(3);

    ImGui::End();
}

void ImGuiHandler::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImGuiHandler::Terminate()
{
    std::cout << "ImGui: Terminated" << std::endl;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}