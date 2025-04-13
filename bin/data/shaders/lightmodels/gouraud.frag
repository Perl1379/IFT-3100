#version 330

in vec3 surface_color;
in vec2 surface_texcoord;

out vec4 fragment_color;

uniform sampler2D textureAlbedo;

void main()
{
    vec4 texColor = texture(textureAlbedo, surface_texcoord);
    vec3 final_color = surface_color * texColor.rgb;
    fragment_color = vec4(final_color, 1.0);
}
