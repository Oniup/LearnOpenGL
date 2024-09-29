#include "Common/GraphicsDevice/Texture.h"
#include "Common/Debug.h"
#include "Common/Utils.h"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture()
      : Id(InvalidId)
{
}

Texture::Texture(const std::string_view& image_path, TextureMode mode, TextureFilter min,
                 TextureFilter mag)
{
    glGenTextures(1, &Id);
    glBindTexture(GL_TEXTURE_2D, Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

    int      channels;
    uint8_t* image_data = stbi_load(image_path.data(), &Size.x, &Size.y, &channels, 0);
    ASSERT(image_data, "Failed to create image from path {}", image_path);

    uint32_t format = 0;
    switch (channels)
    {
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, Size.x, Size.y, 0, format, GL_UNSIGNED_BYTE,
                 image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image_data);
}

void Texture::Destroy()
{
    glDeleteTextures(1, &Id);
    Id = InvalidId;
}

void Texture::Bind(uint32_t active_index)
{
    glActiveTexture(GL_TEXTURE0 + active_index);
    glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture::Unbind(uint32_t active_index)
{
    glActiveTexture(GL_TEXTURE0 + active_index);
    glBindTexture(GL_TEXTURE_2D, 0);
}
