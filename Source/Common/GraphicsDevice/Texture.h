#pragma once

#include <glm/glm.hpp>
#include <string_view>

enum TextureMode
{
    TextureMode_Repeat         = 0x2901,
    TextureMode_MirroredRepeat = 0x8370,
    TextureMode_ClampToEdge    = 0x812F,
    TextureMode_ClampToBorder  = 0x812D,
};

enum TextureFilter
{
    TextureFilter_Nearest              = 0x2600,
    TextureFilter_Linear               = 0x2601,
    TextureFilter_NearestMipmapNearest = 0x2700,
    TextureFilter_LinearMipmapNearest  = 0x2701,
    TextureFilter_NearestMipmapLinear  = 0x2702,
    TextureFilter_LinearMipmapLinear   = 0x2703,
};

struct Texture
{
    glm::ivec2 Size;
    uint32_t   Id;

    Texture();
    Texture(const std::string_view& image_path, TextureMode mode, TextureFilter min,
            TextureFilter mag);

    void Destroy();
    void Bind(uint32_t active_index);
    void Unbind(uint32_t active_index);
};
