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
    bool ImGuiEnabled;

    Context(const std::string_view& title, bool enable_imgui);
    ~Context();

    bool BeginUpdate();
    void EndUpdate();
};
