#pragma once

#include "glm/glm.hpp"

struct Camera
{
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Eye;

    glm::mat4 LookAt(const glm::vec3& target_position);
    glm::mat4 FpsController();
};
