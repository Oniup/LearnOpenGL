#pragma once

#include "Common/Input.h"
#include "Common/Window.h"
#include <imgui.h>
#include <string_view>

struct Context
{
    WindowHandle Window;
    struct Input Input;
    float DeltaTime;

    Context(const std::string_view& win_title, int win_flags = WindowHandle::DefaultFlags);
    ~Context();

    bool BeginFrame();
    void EndFrame();
};
