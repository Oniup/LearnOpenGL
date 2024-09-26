#include "Common/Context.h"
#include "Common/Debug.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

#define VERTEX_BUFFER 0
#define ELEMENT_BUFFER 1

constexpr const char* g_VertShaderSource = "#version 450 core\n"
                                           "layout (location = 0) in vec3 a_Position;"
                                           "void main() "
                                           "{"
                                           "    gl_Position = vec4(a_Position.xyz, 1.0);"
                                           "}";

constexpr const char* g_FragShaderSource = "#version 450 core\n"
                                           "out vec4 FragColor;"
                                           "uniform vec3 u_ShapeColor;"
                                           "void main()"
                                           "{"
                                           "    FragColor = vec4(u_ShapeColor.xyz, 1.0f);"
                                           "}";

uint32_t CreateShaderProgram()
{
    uint32_t vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    for (uint32_t i = 0; i < 2; i++)
    {
        uint32_t shader    = i == 0 ? vertex_shader : fragment_shader;
        const char* source = i == 0 ? g_VertShaderSource : g_FragShaderSource;

        // Shader Source: https://docs.gl/gl4/glShaderSource
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char info_log[512];
            glGetShaderInfoLog(shader, 512, nullptr, info_log);
            FATAL("Failed to compile {} shader: {}", i == 0 ? "vertex" : "fragment", info_log);
        }
    }

    uint32_t program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        FATAL("Failed to link shader program's vertex and fragment shaders: {}", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

int main()
{
    Context context("Hello Square", WindowHandle::DefaultFlags | WindowHandle_EnableImGuiBit);

    glm::vec3 vertices[] = {
        glm::vec3(0.5f, 0.5f, 0.0f),   // top right
        glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
        glm::vec3(-0.5f, -0.5f, 0.0f), // bottom left
        glm::vec3(-0.5f, 0.5f, 0.0f)   // top left
    };

    glm::vec3 clear_color(0.2f, 0.5f, 0.9f);
    glm::vec3 shape_color(0.9f, 0.5f, 0.5f);

    uint32_t indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    uint32_t shader = CreateShaderProgram();

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    int max_vertex_attrib_count;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attrib_count);

    bool wire_frame_mode = false;
    while (context.BeginFrame())
    {
        glClearColor(clear_color.r, clear_color.g, clear_color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (ImGui::Begin("Config###" EXEC_NAME))
        {
            if (ImGui::CollapsingHeader("Options", ImGuiTreeNodeFlags_DefaultOpen))
            {
                bool prev_switch_draw_mode = wire_frame_mode;
                ImGui::Checkbox("Wireframe Mode", &wire_frame_mode);
                if (prev_switch_draw_mode != wire_frame_mode)
                {
                    if (wire_frame_mode)
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    else
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }

                ImGui::ColorEdit3("Background color", (float*)&clear_color);
                ImGui::ColorEdit3("Square color", (float*)&shape_color);
            }
            if (ImGui::CollapsingHeader("About"))
            {
                ImGui::Text("Max number of vertex attributes your gpu supports: %d",
                            max_vertex_attrib_count);
            }
            ImGui::End();
        }

        glUseProgram(shader);
        glUniform3f(glGetUniformLocation(shader, "u_ShapeColor"), shape_color.r, shape_color.g,
                    shape_color.b);

        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        context.EndFrame();
    }

    glDeleteProgram(shader);
}
