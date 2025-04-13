#version 330

in vec3 surface_position;
in vec3 surface_normal;
in vec2 surface_texcoord;

out vec4 fragment_color;

uniform vec3 color_ambient;
uniform vec3 color_diffuse;
uniform vec3 color_specular;
uniform float mat_shininess;

uniform int light_sources;
uniform vec3 global_ambient_color;

uniform int  light_type[8];
uniform vec3 light_position[8];
uniform vec3 light_orientation[8];
uniform float light_attenuation[8];
uniform vec3 light_color_ambient[8];
uniform vec3 light_color_diffuse[8];
uniform vec3 light_color_specular[8];

uniform sampler2D textureAlbedo;
uniform sampler2D textureNormal; // Pas utilisé pour l'instant

void main()
{
    vec4 texColor = texture(textureAlbedo, surface_texcoord);

    vec3 n = normalize(surface_normal);
    vec3 v = normalize(-surface_position);

    vec3 final_ambient = vec3(0.0);
    vec3 final_diffuse = vec3(0.0);
    vec3 final_specular = vec3(0.0);

    for (int i = 0; i < light_sources; ++i)
    {
        vec3 l = normalize(light_position[i] - surface_position);
        vec3 r = reflect(-l, n);

        float dist = length(light_position[i] - surface_position);
        float attenuation = 1.0 / (0.1 + light_attenuation[i] * dist);

        float reflection_diffuse = max(dot(n, l), 0.0);
        float reflection_specular = pow(max(dot(r, v), 0.0), mat_shininess);

        vec3 ambient = light_color_ambient[i] * color_ambient;
        vec3 diffuse = light_color_diffuse[i] * color_diffuse * reflection_diffuse;
        vec3 specular = light_color_specular[i] * color_specular * reflection_specular;
        final_ambient += ambient * attenuation;
        final_diffuse += diffuse * reflection_diffuse * attenuation;
        final_specular += specular * reflection_specular * attenuation;
    }

    vec3 final_color = (final_ambient + final_diffuse + final_specular + global_ambient_color) * texColor.rgb;
    fragment_color = vec4(final_color, 1.0);
}
