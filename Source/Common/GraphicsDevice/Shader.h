#pragma once

#include <cinttypes>
#include <limits>
#include <string>

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

    static std::string_view TypeToString(Type type);
    static std::string      Read(const std::string_view& shader_path);

private:
    uint32_t m_Program = std::numeric_limits<uint32_t>::max();
};
