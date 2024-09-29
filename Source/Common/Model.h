#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 Uv;
};

struct Model
{
    std::vector<Vertex>   Vertices;
    std::vector<uint32_t> Indices;
};

Model CreateSphere(uint32_t segments_x, uint32_t segments_y);
Model CreatePlane();
Model CreateCube();
