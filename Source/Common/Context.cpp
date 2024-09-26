#include "Common/Context.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <filesystem>
#include <fmt/format.h>
#include <glad/glad.h>
#include <imgui.h>

Context::Context(const std::string_view& title, bool enable_imgui)
      : ImGuiEnabled(enable_imgui)
{
    WindowHandle::InitializeGLFW();
    Window.Initialize(fmt::format("Learning OpenGL - {}", title), -1, -1);
    Input.Initialize(Window);

    if (enable_imgui) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;

        std::filesystem::path path = std::filesystem::current_path();
        path.append("Assets/Fonts/DroidSans.ttf");
        path.make_preferred();

        io.Fonts->AddFontFromFileTTF(path.c_str(), 16.0f);
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(Window.WindowPtr, true);
        ImGui_ImplOpenGL3_Init("#version 450");
    }
}

Context::~Context()
{
    if (ImGuiEnabled) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    Window.Destroy();
    WindowHandle::DestroyGLFW();
}

bool Context::BeginFrame()
{
    if (Window.Closing()) {
        return false;
    }

    Input.PollEvents();

    static float last_time = 0.0f;
    float time             = glfwGetTime();
    DeltaTime              = time - last_time;
    last_time              = time;

    if (ImGuiEnabled) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    return true;
}

void Context::EndFrame()
{
    if (ImGuiEnabled) {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    Window.SwapBuffers();
}
