#include "Common/Context.h"
#include "Common/GraphicsDevice/Shader.h"
#include "Common/GraphicsDevice/Texture.h"
#include "imgui.h"
#include <Common/Model.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define VERTEX_BUFFER  0
#define ELEMENT_BUFFER 1

int main()
{
    Context context(EXEC_NAME, WindowHandle::DefaultFlags | WindowHandle_EnableImGuiBit);

    glEnable(GL_DEPTH_TEST);

    Model Cube = CreateCube();

    glm::vec3 clear_color(0.2f, 0.5f, 0.9f);

    Shader shader({
        ShaderSource(DIR_PATH "/Vertex.glsl", ShaderType_Vertex),
        ShaderSource(DIR_PATH "/Fragment.glsl", ShaderType_Fragment),
    });

    Texture texture("Assets/WoodenCrate/textures/Crate_baseColor.png", TextureMode_Repeat,
                    TextureFilter_LinearMipmapLinear, TextureFilter_Linear);

    uint32_t vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    uint32_t buffer_objects[2];
    glGenBuffers(2, buffer_objects);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_objects[VERTEX_BUFFER]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_objects[ELEMENT_BUFFER]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Cube.Vertices.size(), Cube.Vertices.data(),
                 GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * Cube.Indices.size(),
                 Cube.Indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Uv));

    int max_vertex_attrib_count;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attrib_count);

    glm::vec3 transform_position(0.0f);
    glm::vec3 transform_scale(0.5f);
    glm::vec4 transform_rotate(0.0f, 0.0f, 1.0f, 0.0f);

    float     fov        = 45.0f;
    glm::mat4 projection = glm::perspective(glm::radians(fov),
                                            (float)context.Window.FramebufferSize().x /
                                                (float)context.Window.FramebufferSize().y,
                                            0.1f, 100.0f);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    bool wire_frame_mode = false;
    bool show_uv_map     = false;
    while (context.BeginFrame())
    {
        glClearColor(clear_color.r, clear_color.g, clear_color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        bool       prev_switch_draw_mode = wire_frame_mode;
        float      prev_fov              = fov;
        glm::ivec2 prev_win_size         = context.Window.FramebufferSize();

        if (ImGui::Begin("Options###" EXEC_NAME))
        {
            ImGui::Checkbox("Wireframe Mode", &wire_frame_mode);
            ImGui::Checkbox("Show UV Map", &show_uv_map);

            if (ImGui::CollapsingHeader("Shape"))
            {
                // Colors
                ImGui::ColorEdit3("Background color", (float*)&clear_color);
                if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    ImGui::DragFloat3("Position", &transform_position[0], 0.1f);
                    ImGui::DragFloat3("Scale", &transform_scale[0], 0.1f);
                    ImGui::DragFloat3("Rotation Axis", &transform_rotate[0], 0.1f, 0.0f, 1.0f);
                    ImGui::DragFloat("Rotate", &transform_rotate.w, 1.0f);
                }
            }

            if (ImGui::CollapsingHeader("Camera "))
            {
                ImGui::DragFloat("Fov", &fov, 1.0f, 10.0f, 120.0f);
            }
            ImGui::End();
        }

        if (prev_switch_draw_mode != wire_frame_mode)
        {
            if (wire_frame_mode)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (prev_fov != fov || prev_win_size != context.Window.FramebufferSize())
        {

            float aspect = (float)context.Window.FramebufferSize().x /
                           (float)context.Window.FramebufferSize().y;
            projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
        }

        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, transform_position);
        transform = glm::scale(transform, transform_scale);
        transform =
            glm::rotate(transform, glm::radians(transform_rotate.w), glm::vec3(transform_rotate));

        texture.Bind(0);

        shader.Bind();
        shader.UniformI("u_ShowUvMap", (int)show_uv_map);
        shader.UniformMat4("u_Model", transform);
        shader.UniformMat4("u_View", view);
        shader.UniformMat4("u_Projection", projection);

        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, Cube.Indices.size(), GL_UNSIGNED_INT, 0);

        context.EndFrame();
    }

    shader.Destroy();
    texture.Destroy();
}
