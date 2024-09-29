#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_UV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 o_UV;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position.xyz, 1.0);
    o_UV = a_UV;
}
