#include "Common/Camera.h"
#include "Common/Input.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up)
      : Position(position), Forward(forward), Up(up)
{
}

glm::mat4 Camera::LookAt(const glm::vec3& target_position)
{
    return glm::mat4(1.0f);
}

glm::mat4 Camera::FpsController(float speed, float sensitivity)
{
    static glm::vec2 last_cursor_position(0.0f);
    static bool      first_mouse_position = true;
    static float     yaw                  = 0.0f;
    static float     pitch                = 0.0f;

    glm::vec2 cursor_position = Input::GetCursorPosition();
    if (Input::MousePress(MouseButton_Right))
    {
        glm::vec2 offset(cursor_position.x - last_cursor_position.x,
                         last_cursor_position.y - cursor_position.y);
        last_cursor_position = cursor_position;

        offset *= sensitivity;
        yaw += offset.x;
        pitch += offset.y;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        Forward = glm::vec3(glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
                            glm::sin(glm::radians(pitch)),
                            glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch)));
        Forward = glm::normalize(Forward);
    }
    else
        last_cursor_position = cursor_position;

    if (Input::KeyPress(KeyCode_LeftShift))
        speed *= 2;

    if (Input::KeyPress(KeyCode_W))
        Position += speed * Forward;
    if (Input::KeyPress(KeyCode_S))
        Position -= speed * Forward;
    if (Input::KeyPress(KeyCode_A))
        Position += speed * glm::normalize(glm::cross(Up, Forward));
    if (Input::KeyPress(KeyCode_D))
        Position -= speed * glm::normalize(glm::cross(Up, Forward));
    if (Input::KeyPress(KeyCode_Space))
        Position += speed * Up;
    if (Input::KeyPress(KeyCode_LeftControl))
        Position -= speed * Up;

    glm::mat4 view = glm::lookAt(Position, Position + Forward, Up);
    return view;
}
