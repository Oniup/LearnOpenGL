#include "Common/GraphicsDevice/Shader.h"
#include "Common/Debug.h"
#include <cstdio>
#include <fmt/format.h>
#include <glad/glad.h>

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
