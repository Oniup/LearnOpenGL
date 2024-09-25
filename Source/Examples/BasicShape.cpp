#define GLFW_INCLUDE_NONE

#include "Common/Debug.h"
#include "Common/Input.h"
#include "Common/Window.h"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <filesystem>
#include <glad/glad.h>
#include <imgui.h>

int main()
{
    WindowHandle window;
    Input input;

    WindowHandle::InitializeGLFW();
    window.Initialize("Learning OpenGL - BasicShape", -1, -1);
    input.Initialize(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;

    std::filesystem::path path = std::filesystem::current_path();
    path.append("Assets/Fonts/DroidSans.ttf");
    path.make_preferred();

    io.Fonts->AddFontFromFileTTF(path.c_str(), 16.0f);
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.WindowPtr, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    while (!window.Closing()) {
        input.PollEvents();

        glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw
        {
            // ...
        }

        // ImGui
        {
            ImGui::Begin("Test");
            if (ImGui::Button("Print message")) {
                Message("Printing message...");
            }
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.Destroy();

    WindowHandle::DestroyGLFW();
}
