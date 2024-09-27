#include "Common/GraphicsDevice/Shader.h"
#include "Common/Debug.h"
#include <cstdio>
#include <fmt/format.h>
#include <glad/glad.h>

std::string_view Shader::TypeToString(Type type)
{
    switch (type)
    {
    case Fragment:
        return "Fragment";
    case Vertex:
        return "Vertex";
    case Geometry:
        return "Geometry";
    case Compute:
        return "Compute";
    default:
        return "Invalid";
    }
}

std::string Shader::Read(const std::string_view& shader_path)
{
    std::FILE* file = std::fopen(shader_path.data(), "rb");
    ASSERT(file, "Shader file path {} doesn't exist", shader_path);

    std::fseek(file, 0, SEEK_END);
    size_t size = std::ftell(file);
    std::fseek(file, 0, SEEK_SET);

    std::string source;
    source.reserve(size);
    char line[1024];
    while (std::fgets(line, sizeof(line), file) != nullptr)
    {
        source += line;
    }

    return source;
}

Shader::Shader(const std::vector<Source>& sources)
{
    std::vector<uint32_t> shader_ids(sources.size());
    for (const Source& source : sources)
    {
    }
}

void Shader::Destroy()
{
}

void Shader::Bind()
{
}

void Shader::Unbind()
{
}

void Shader::UniformI(const std::string_view& location, uint32_t val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform1i(glGetUniformLocation(m_Program, location.data()), val);
}

void Shader::UniformI2(const std::string_view& location, const glm::ivec2& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform2i(glGetUniformLocation(m_Program, location.data()), val.x, val.y);
}

void Shader::UniformI3(const std::string_view& location, const glm::ivec3& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform3i(glGetUniformLocation(m_Program, location.data()), val.x, val.y, val.z);
}

void Shader::UniformI4(const std::string_view& location, const glm::ivec4& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform4i(glGetUniformLocation(m_Program, location.data()), val.x, val.y, val.z, val.w);
}

void Shader::UniformF(const std::string_view& location, float val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform1f(glGetUniformLocation(m_Program, location.data()), val);
}

void Shader::UniformF2(const std::string_view& location, const glm::vec2& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform2f(glGetUniformLocation(m_Program, location.data()), val.x, val.y);
}

void Shader::UniformF3(const std::string_view& location, const glm::vec3& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform3f(glGetUniformLocation(m_Program, location.data()), val.x, val.y, val.z);
}

void Shader::UniformF4(const std::string_view& location, const glm::vec4& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform4f(glGetUniformLocation(m_Program, location.data()), val.x, val.y, val.z, val.w);
}

void Shader::UniformMat2(const std::string_view& location, const glm::mat2& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniformMatrix2fv(glGetUniformLocation(m_Program, location.data()), 1, GL_FALSE, &val[0][0]);
}

void Shader::UniformMat3(const std::string_view& location, const glm::mat3& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniformMatrix3fv(glGetUniformLocation(m_Program, location.data()), 1, GL_FALSE, &val[0][0]);
}

void Shader::UniformMat4(const std::string_view& location, const glm::mat4& val)
{
    ASSERT(m_Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniformMatrix4fv(glGetUniformLocation(m_Program, location.data()), 1, GL_FALSE, &val[0][0]);
}
