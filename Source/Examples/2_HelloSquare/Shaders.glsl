Vertex:
layout (location = 0) in vec3 a_Position;

void main() 
{
    gl_Position = vec4(a_Position.xyz, 1.0);
}

Fragment:
out vec4 FragColor;

uniform vec3 u_ShapeColor;

void main()
{
    FragColor = vec4(u_ShapeColor.xyz, 1.0f);
}
