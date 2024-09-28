#pragma once

#include "Common/Utils.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

enum ShaderType
{
    ShaderType_Fragment = 0x8B30,
    ShaderType_Vertex   = 0x8B31,
    ShaderType_Geometry = 0x8DD9,
    ShaderType_Compute  = 0x91B9,
    ShaderType_Invalid  = -1,
};

struct ShaderSource
{
    std::string Source;
    ShaderType  Type;

    ShaderSource(const std::string_view& path, ShaderType type);
};

struct Shader
{
    uint32_t Program;

    Shader() = default;
    Shader(const std::vector<ShaderSource>& sources);

    void Destroy();
    void Bind();
    void Unbind();

    void UniformI(const std::string_view& location, uint32_t val);
    void UniformI2(const std::string_view& location, const glm::ivec2& val);
    void UniformI3(const std::string_view& location, const glm::ivec3& val);
    void UniformI4(const std::string_view& location, const glm::ivec4& val);

    void UniformF(const std::string_view& location, float val);
    void UniformF2(const std::string_view& location, const glm::vec2& val);
    void UniformF3(const std::string_view& location, const glm::vec3& val);
    void UniformF4(const std::string_view& location, const glm::vec4& val);

    void UniformMat2(const std::string_view& location, const glm::mat2& val);
    void UniformMat3(const std::string_view& location, const glm::mat3& val);
    void UniformMat4(const std::string_view& location, const glm::mat4& val);
};

std::string_view ShaderTypeToString(ShaderType type);
