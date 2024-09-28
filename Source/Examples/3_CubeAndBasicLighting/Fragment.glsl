#version 450 core

uniform vec3 u_ShapeColor;
uniform int u_ShowUvMap;
in vec2 o_UV;

out vec4 FragColor;

void main()
{
    vec3 color = u_ShapeColor * (1.0f - u_ShowUvMap);
    FragColor = vec4(
            color.x + o_UV.x * u_ShowUvMap,
            color.y + o_UV.y * u_ShowUvMap,
            color.z + u_ShowUvMap,
            1.0f
        );
}
