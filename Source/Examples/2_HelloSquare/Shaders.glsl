Vertex:
layout (location = 0) in vec3 a_Position;

void main() 
{
    gl_Position = vec4(a_Position.xyz, 1.0);
}

Fragment:
out vec4 FragmentColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
