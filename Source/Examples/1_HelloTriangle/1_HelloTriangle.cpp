#include "Common/Context.h"
#include "Common/Debug.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

constexpr const char* g_VertShaderSource = "#version 450 core\n"
                                           "layout (location = 0) in vec3 a_Position;"
                                           "void main() "
                                           "{"
                                           "    gl_Position = vec4(a_Position.xyz, 1.0);"
                                           "}";

constexpr const char* g_FragShaderSource = "#version 450 core\n"
                                           "out vec4 FragColor;"
                                           "void main()"
                                           "{"
                                           "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
                                           "}";

uint32_t CreateShaderProgram()
{
    uint32_t vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    for (uint32_t i = 0; i < 2; i++)
    {
        uint32_t    shader = i == 0 ? vertex_shader : fragment_shader;
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
    Context context(EXEC_NAME);

    glm::vec3 vertices[] = {
        glm::vec3(-0.5f, -0.5f, 0.0f), // Left
        glm::vec3(0.5f, -0.5f, 0.0f),  // Right
        glm::vec3(0.0f, 0.5f, 0.0f),   // Top
    };

    uint32_t program = CreateShaderProgram();

    uint32_t vertex_array;
    uint32_t vertex_buffer;
    // Create vertex array object that associates the following buffers objects
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Create vertex buffer object
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Associates vertex buffer with vertex array object
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    while (context.BeginFrame())
    {
        glClearColor(0.2f, 0.5f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Don't have to call this every frame here but, in a real project with multiple vertex
        // array objects and shaders, you would
        glUseProgram(program);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        context.EndFrame();
    }

    glDeleteProgram(program);
}
