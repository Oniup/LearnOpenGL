#pragma once

#include <glm/glm.hpp>
#include <limits>
#include <string>
#include <vector>

class Shader
{
public:
    enum Type
    {
        Fragment = 0x8B30,
        Vertex   = 0x8B31,
        Geometry = 0x8DD9,
        Compute  = 0x91B9,
        Invalid  = -1,
    };

    struct Source
    {
        std::string_view path;
        Type             type;
    };

public:
    static constexpr uint32_t InvalidId = std::numeric_limits<uint32_t>::max();

    static std::string_view TypeToString(Type type);
    static std::string      Read(const std::string_view& shader_path);

public:
    Shader() = default;
    Shader(const std::vector<Source>& sources);

public:
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

private:
    uint32_t m_Program = InvalidId;
};
