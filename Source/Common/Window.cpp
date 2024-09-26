#include "Common/Window.h"
#include "Common/Debug.h"
#include <glad/glad.h>

static bool s_GladInitialized = false;

void WindowHandle::Initialize(const std::string_view& title, int width, int height, int flags)
{
    ASSERT(title[title.size()] == '\0', "Title string must be null terminated");
    ASSERT(ValidMode(flags), "Can only create window with one or none of the window modes");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, (flags & WindowHandle_ResizeableBit) != 0);
    glfwWindowHint(GLFW_DECORATED, (flags & ~WindowHandle_BorderlessModeBit) != 0);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, (flags & WindowHandle_TransparentBufferBit) != 0);

    GLFWmonitor* monitor       = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
    if (width < 0 | height < 0) {
        width  = vidmode->width / 2;
        height = vidmode->height / 2;
    }

    if (flags & ~WindowHandle_FullscreenModeBit) {
        monitor = nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title.data(), monitor, nullptr);
    ASSERT(window != nullptr, "Failed to create GLFW window");
    glfwMakeContextCurrent(window);

    if (!s_GladInitialized) {
        s_GladInitialized = true;
        ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");
    }

    if (flags & WindowHandle_VsyncBit) {
        glfwSwapInterval(0);
    }
    else {
        glfwSwapInterval(1);
    }

    WindowPtr = window;
    Flags     = flags;
}

void WindowHandle::Destroy()
{
    ASSERT(WindowPtr != nullptr, "WindowHandle is nullptr, Cannot destroy window");
    glfwDestroyWindow(WindowPtr);
    WindowPtr = nullptr;
    Flags     = 0;
}

void WindowHandle::SwapBuffers()
{
    glfwSwapBuffers(WindowPtr);
    glm::ivec2 frame_buffer_size = FramebufferSize();
    glViewport(0, 0, frame_buffer_size.x, frame_buffer_size.y);
}

void WindowHandle::InitializeGLFW()
{
    ASSERT(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");
    glfwSetErrorCallback([](int error, const char* description) {
        ERROR("GLFW", "{} => {}", error, description);
    });
}

void WindowHandle::DestroyGLFW()
{
    glfwTerminate();
}

bool WindowHandle::ValidMode(int flags)
{
    int target = WindowHandle_WindowedModeBit | WindowHandle_BorderlessModeBit |
                 WindowHandle_FullscreenModeBit;
    int enabled = target & flags;
    return enabled == 0 || enabled == WindowHandle_WindowedModeBit ||
           enabled == WindowHandle_BorderlessModeBit || enabled == WindowHandle_FullscreenModeBit;
}

bool WindowHandle::Closing() const
{
    return glfwWindowShouldClose(WindowPtr);
}

const std::string_view WindowHandle::Title() const
{
    return std::string_view(glfwGetWindowTitle(WindowPtr));
}

glm::ivec2 WindowHandle::FramebufferSize() const
{
    glm::ivec2 buffer_size;
    glfwGetFramebufferSize(WindowPtr, &buffer_size.x, &buffer_size.y);
    return buffer_size;
}

glm::ivec2 WindowHandle::Size() const
{
    glm::ivec2 win_size;
    glfwGetWindowSize(WindowPtr, &win_size.x, &win_size.y);
    return win_size;
}

glm::ivec2 WindowHandle::Position() const
{
    glm::ivec2 win_pos;
    glfwGetWindowPos(WindowPtr, &win_pos.x, &win_pos.y);
    return win_pos;
}

void WindowHandle::Close(bool close)
{
    glfwSetWindowShouldClose(WindowPtr, close);
}

void WindowHandle::MakeCurrentContext() const
{
    glfwMakeContextCurrent(WindowPtr);
}
