#version 330

in vec3 surface_position;
in vec3 surface_normal;
in vec2 surface_texcoord;
in mat3 TBN;  // Tangent, Bitangent, Normal matrix

out vec4 fragment_color;

uniform vec3 color_ambient;
uniform vec3 color_diffuse;

uniform int light_sources;
uniform vec3 global_ambient_color;

uniform int  light_type[8];
uniform vec3 light_position[8];
uniform vec3 light_orientation[8];
uniform float light_attenuation[8];
uniform vec3 light_color_ambient[8];
uniform vec3 light_color_diffuse[8];
uniform vec3 light_color_specular[8];
uniform float texture_albedo_scale;

uniform sampler2D textureAlbedo;

void main()
{
    vec4 texColor = texture(textureAlbedo, surface_texcoord * texture_albedo_scale);


    vec3 final_ambient = vec3(0.0);
    vec3 final_diffuse = vec3(0.0);

    for (int i = 0; i < light_sources; ++i)
    {
        vec3 l = normalize(light_position[i] - surface_position);

        float dist = length(light_position[i] - surface_position);
        //float attenuation = 1.0 / (0.1 + light_attenuation[i] * dist);
        float attenuation = 1.0 / (0.1 + light_attenuation[i] * dist);
        attenuation = max(attenuation, 0.01); // Avoid very small or zero attenuation

        float reflection_diffuse = max(dot(surface_normal, l), 0.0);

        vec3 ambient = light_color_ambient[i] * color_ambient;
        vec3 diffuse = light_color_diffuse[i] * color_diffuse * reflection_diffuse;
        final_ambient += ambient;
        final_diffuse += diffuse * attenuation;

    }
    vec3 final_color = final_ambient + final_diffuse + global_ambient_color;
    final_color = (final_ambient * 0.2 + final_diffuse) * texColor.rgb;

    fragment_color = vec4(final_color, 1.0);
}
