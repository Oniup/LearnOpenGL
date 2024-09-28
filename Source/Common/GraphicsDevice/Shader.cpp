#include "Common/GraphicsDevice/Shader.h"
#include "Common/Debug.h"
#include <cstdio>
#include <fmt/format.h>
#include <glad/glad.h>

ShaderSource::ShaderSource(const std::string_view& path, ShaderType type)
      : Source(ReadSource(path)), Type(type)
{
}

std::string_view ShaderTypeToString(ShaderType type)
{
    switch (type)
    {
    case ShaderType_Fragment:
        return "Fragment";
    case ShaderType_Vertex:
        return "Vertex";
    case ShaderType_Geometry:
        return "Geometry";
    case ShaderType_Compute:
        return "Compute";
    default:
        return "Invalid";
    }
}

Shader::Shader(const std::vector<ShaderSource>& sources)
{
    std::vector<uint32_t> shader_ids;
    shader_ids.reserve(sources.size());
    for (const ShaderSource& source : sources)
    {
        if (source.Source.size() < 17)
        {
            FATAL("Failed to compile {} shader, Source doesn't exist",
                  ShaderTypeToString(source.Type));
        }

        uint32_t    shader     = glCreateShader((uint32_t)source.Type);
        const char* ptr_source = source.Source.c_str();

        glShaderSource(shader, 1, &ptr_source, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            constexpr size_t log_size = 1024;
            char             info_log[log_size];
            glGetShaderInfoLog(shader, log_size, nullptr, info_log);
            FATAL("Failed to compile {} shader\nOpenGL Error:\n{}\n{}",
                  ShaderTypeToString(source.Type), info_log, source.Source);
        }

        shader_ids.push_back(shader);
    }

    Program = glCreateProgram();
    for (uint32_t shader : shader_ids)
        glAttachShader(Program, shader);
    glLinkProgram(Program);

    int success;
    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        constexpr size_t log_size = 1024;
        char             info_log[log_size];
        glGetProgramInfoLog(Program, log_size, nullptr, info_log);
        FATAL("Failed to link compiled shaders to program");
    }

    for (uint32_t shader : shader_ids)
        glDeleteShader(shader);
}

void Shader::Destroy()
{
    glDeleteProgram(Program);
    Program = InvalidId;
}

void Shader::Bind()
{
    glUseProgram(Program);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::UniformI(const std::string_view& location, uint32_t val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform1i(glGetUniformLocation(Program, location.data()), val);
}

void Shader::UniformI2(const std::string_view& location, const glm::ivec2& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform2i(glGetUniformLocation(Program, location.data()), val.x, val.y);
}

void Shader::UniformI3(const std::string_view& location, const glm::ivec3& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform3i(glGetUniformLocation(Program, location.data()), val.x, val.y, val.z);
}

void Shader::UniformI4(const std::string_view& location, const glm::ivec4& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform4i(glGetUniformLocation(Program, location.data()), val.x, val.y, val.z, val.w);
}

void Shader::UniformF(const std::string_view& location, float val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform1f(glGetUniformLocation(Program, location.data()), val);
}

void Shader::UniformF2(const std::string_view& location, const glm::vec2& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform2f(glGetUniformLocation(Program, location.data()), val.x, val.y);
}

void Shader::UniformF3(const std::string_view& location, const glm::vec3& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform3f(glGetUniformLocation(Program, location.data()), val.x, val.y, val.z);
}

void Shader::UniformF4(const std::string_view& location, const glm::vec4& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniform4f(glGetUniformLocation(Program, location.data()), val.x, val.y, val.z, val.w);
}

void Shader::UniformMat2(const std::string_view& location, const glm::mat2& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniformMatrix2fv(glGetUniformLocation(Program, location.data()), 1, GL_FALSE, &val[0][0]);
}

void Shader::UniformMat3(const std::string_view& location, const glm::mat3& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniformMatrix3fv(glGetUniformLocation(Program, location.data()), 1, GL_FALSE, &val[0][0]);
}

void Shader::UniformMat4(const std::string_view& location, const glm::mat4& val)
{
    ASSERT(Program != InvalidId,
           "Cannot push constant to shader program. Must create shader instance first");
    glUniformMatrix4fv(glGetUniformLocation(Program, location.data()), 1, GL_FALSE, &val[0][0]);
}
