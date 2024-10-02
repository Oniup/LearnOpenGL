#pragma once

#include "Common/InputKeyCodes.h"
#include "Common/Window.h"
#include <array>
#include <string_view>

enum InputType
{
    InputType_Unknown = -1,
    InputType_Keyboard,
    InputType_Mouse,
    InputType_GamePad,
};

enum MouseMode
{
    MouseMode_Invalid = -1,
    MouseMode_Visable,
    MouseMode_Hidden,
    MouseMode_Captured,

};

struct RegisteredInput
{
    InputType Type           = InputType_Unknown;
    int       Code           = -1;
    bool      RemoveNextTick = false;
    bool      Pressed        = false;
};

struct Input
{
    static constexpr size_t RegisterOnceBufferSize = 16;

    WindowHandle*                                       WindowPtr      = nullptr;
    size_t                                              RegActiveCount = 0;
    std::array<RegisteredInput, RegisterOnceBufferSize> RegBuffer;

    void Initialize(WindowHandle& window);

    static bool KeyPressed(KeyCode code);
    static bool KeyReleased(KeyCode code);

    static bool KeyPress(KeyCode code);
    static bool KeyRelease(KeyCode code);

    static bool MousePressed(MouseButton button);
    static bool MouseReleased(MouseButton button);

    static bool MousePress(MouseButton button);
    static bool MouseRelease(MouseButton button);
    static glm::vec2 GetCursorPosition();

    static std::string_view TypeToString(InputType type);
    static std::string_view MouseModeToString(MouseMode mode);

    void PollEvents();

private:
    bool _RegisterOnce(InputType type, int code, bool pressed);
};
