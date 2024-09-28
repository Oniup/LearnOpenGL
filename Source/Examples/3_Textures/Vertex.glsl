#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UV;

uniform mat4 u_Transform;

out vec2 o_UV;

void main()
{
    gl_Position = u_Transform * vec4(a_Position.xyz, 1.0);
    o_UV = a_UV;
}
