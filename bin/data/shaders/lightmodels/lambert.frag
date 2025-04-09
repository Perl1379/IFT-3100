#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

// couleurs de réflexion du matériau
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


uniform sampler2D textureAlbedo;
uniform sampler2D textureNormal; // Pas utilisé pour l'instant


void main()
{
    vec4 texColor = texture(textureAlbedo, surface_texcoord);

    vec3 n = normalize(surface_normal);

    vec3 final_ambient = vec3(0.0);
    vec3 final_diffuse = vec3(0.0);

    for (int i = 0; i < light_sources; ++i)
    {
        vec3 l = normalize(light_position[i] - surface_position);

        float constantAttenuation = 0.1; // Pour éviter la division par zéro
        float linearAttenuation = light_attenuation[i];

        // Attenuation linéaire basé sur la distance entre la source de lumière et la surface
        float dist = length(light_position[i] - surface_position);
        float attenuation = 1.0 / (constantAttenuation + linearAttenuation * dist);

        float reflection_diffuse = max(dot(n, l), 0.0);

        vec3 ambient = light_color_ambient[i] * color_ambient;
        vec3 diffuse = light_color_diffuse[i] * color_diffuse * reflection_diffuse;
        final_ambient += ambient * attenuation;
        final_diffuse += diffuse * reflection_diffuse * attenuation;
    }

    vec3 final_color = (final_ambient + final_diffuse) * texColor.rgb;
    final_color += global_ambient_color;
    fragment_color = vec4(final_color, 1.0);

}
