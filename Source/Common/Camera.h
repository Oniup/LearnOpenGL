#pragma once

#include "glm/glm.hpp"

struct Camera
{
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Up;

    Camera(const glm::vec3& position = glm::vec3(0.0f),
           const glm::vec3& forward  = glm::vec3(0.0f, 0.0f, -1.0f),
           const glm::vec3& up       = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 LookAt(const glm::vec3& target_position);
    glm::mat4 FpsController(float speed, float sensitivity);
};
