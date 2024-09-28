#include "Common/Context.h"
#include "Common/Debug.h"
#include "Common/GraphicsDevice/Shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb/stb_image.h>

#define VERTEX_BUFFER  0
#define ELEMENT_BUFFER 1

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 UV;
};

uint32_t CreateTexture()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int                        width, height, nrChannels;
    constexpr std::string_view path = "Assets/WoodenCrate/textures/Crate_baseColor.png";
    unsigned char*             data = stbi_load(path.data(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        FATAL("Failed to load texture at {}", path);
    }
    stbi_image_free(data);
    return texture;
}

int main()
{
    Context context(EXEC_NAME, WindowHandle::DefaultFlags | WindowHandle_EnableImGuiBit);

    Vertex vertices[] = {
        Vertex {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)},   // top right
        Vertex {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
        Vertex {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)}, // bottom left
        Vertex {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)},  // top left
    };

    glm::vec3 clear_color(0.2f, 0.5f, 0.9f);

    uint32_t indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shader({
        ShaderSource(DIR_PATH "/Vertex.glsl", ShaderType_Vertex),
        ShaderSource(DIR_PATH "/Fragment.glsl", ShaderType_Fragment),
    });

    uint32_t texture = CreateTexture();

    uint32_t vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    uint32_t buffer_objects[2];
    glGenBuffers(2, buffer_objects);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[VERTEX_BUFFER]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_objects[ELEMENT_BUFFER]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

    int max_vertex_attrib_count;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attrib_count);

    bool wire_frame_mode = false;
    bool show_uv_map     = false;
    while (context.BeginFrame())
    {
        glClearColor(clear_color.r, clear_color.g, clear_color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        bool prev_switch_draw_mode = wire_frame_mode;
        if (ImGui::Begin("Options###" EXEC_NAME))
        {
            // Toggle Modes
            ImGui::Checkbox("Wireframe Mode", &wire_frame_mode);
            ImGui::Checkbox("Show UV Map", &show_uv_map);
            // Colors
            ImGui::ColorEdit3("Background color", (float*)&clear_color);
            ImGui::End();
        }

        if (prev_switch_draw_mode != wire_frame_mode)
        {
            if (wire_frame_mode)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        shader.Bind();
        shader.UniformI("u_ShowUvMap", (int)show_uv_map);

        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        context.EndFrame();
    }

    shader.Destroy();
    glDeleteTextures(1, &texture);
}
