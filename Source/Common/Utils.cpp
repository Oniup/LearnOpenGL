#include "Common/Utils.h"
#include "Common/Debug.h"

std::string ReadSource(const std::string_view& file_path)
{
    std::FILE* file = std::fopen(file_path.data(), "rb");
    ASSERT(file, "Shader file path {} doesn't exist", file_path);

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
