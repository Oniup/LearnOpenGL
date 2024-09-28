#version 450 core

uniform int u_ShowUvMap;
uniform sampler2D u_Texture;
in vec2 o_UV;

out vec4 FragColor;

void main()
{
    vec4 color = texture(u_Texture, o_UV) * (1.0f - u_ShowUvMap);
    FragColor = vec4(
            color.x + o_UV.x * u_ShowUvMap,
            color.y + o_UV.y * u_ShowUvMap,
            color.z + u_ShowUvMap,
            color.w
        );
    // FragColor = texture(u_Texture, o_UV);
}
