#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string_view>

enum WindowHandleFlags
{
    WindowHandle_NoneBit              = 0,
    WindowHandle_WindowedModeBit      = 1 << 0,
    WindowHandle_BorderlessModeBit    = 1 << 1,
    WindowHandle_FullscreenModeBit    = 1 << 2,
    WindowHandle_VsyncBit             = 1 << 3,
    WindowHandle_TrippleBufferBit     = 1 << 4,
    WindowHandle_ResizeableBit        = 1 << 5,
    WindowHandle_TransparentBufferBit = 1 << 6,
    WindowHandle_EnableImGuiBit       = 1 << 7,
};

struct WindowHandle
{
    static constexpr int DefaultFlags =
        WindowHandle_ResizeableBit | WindowHandle_VsyncBit | WindowHandle_WindowedModeBit;

    GLFWwindow* WindowPtr = nullptr;
    int         Flags     = DefaultFlags;

    static void InitializeGLFW();
    static void DestroyGLFW();
    static bool ValidMode(int flags);

    void Initialize(const std::string_view& title, int width, int height,
                    int flags = DefaultFlags);
    void Destroy();
    bool Closing() const;
    void SwapBuffers();
    void Close(bool close = true);
    void MakeCurrentContext() const;

    inline bool            Valid() const { return WindowPtr != nullptr; }
    const std::string_view Title() const;
    glm::ivec2             FramebufferSize() const;
    glm::ivec2             Size() const;
    glm::ivec2             Position() const;
};
