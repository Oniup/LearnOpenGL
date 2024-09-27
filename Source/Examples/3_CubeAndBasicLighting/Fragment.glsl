#version 450 core

uniform vec3 u_ShapeColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(u_ShapeColor.xyz, 1.0f);
}
