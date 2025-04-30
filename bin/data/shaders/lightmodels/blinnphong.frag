#version 420

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
uniform float texture_albedo_scale;
uniform float texture_normal_scale;

layout(binding=0) uniform sampler2D texture_albedo;
layout(binding=1) uniform sampler2D texture_normal;

void main()
{
    vec4 texture_color = texture(texture_albedo, surface_texcoord * texture_albedo_scale);
    vec3 normal_color = texture(texture_normal, surface_texcoord * texture_normal_scale).rgb * 2.0 - 1.0;
    vec3 perturbed_normal = normalize(vec3(
                                      surface_normal.x + normal_color.x * 0.3,
                                      surface_normal.y + normal_color.y * 0.3,
                                      surface_normal.z
                                      ));

    vec3 n = perturbed_normal;
    vec3 v = normalize(-surface_position);

    vec3 final_ambient = global_ambient_color;
    vec3 final_diffuse = vec3(0.0);
    vec3 final_specular = vec3(0.0);

    for (int i = 0; i < light_sources; ++i)
    {
        vec3 l;
        float attenuation = 1.0;

//        vec3 l = normalize(light_position[i] - surface_position);


        // Lumière directionnelle
        if (light_type[i] == 2)
        {
            l = normalize(light_orientation[i]);
        }
        // Lumière ponctuelle
        else if (light_type[i] == 1)
        {
            l = normalize(light_position[i] - surface_position);
            float dist = length(light_position[i] - surface_position);
            attenuation = 1.0 / (0.1 + light_attenuation[i] * dist);
            attenuation = max(attenuation, 0.01);
        }
        // Projecteur
        else if (light_type[i] == 0)
        {
            l = normalize(light_position[i] - surface_position);
            float spot_factor = dot(normalize(light_orientation[i]), -l);
            if (spot_factor < 0.0) {
                spot_factor = 0.0;
            }
            float dist = length(light_position[i] - surface_position);
            attenuation = 1.0 / (0.1 + light_attenuation[i] * dist);
            attenuation = max(attenuation, 0.01);

            float spot_threshold = 0.9;
            spot_factor = smoothstep(spot_threshold, 1.0, spot_factor);
            attenuation *= spot_factor;
        }


        vec3 h = normalize(l + v); // vecteur halfway

        float reflection_diffuse = max(dot(n, l), 0.0);
        float reflection_specular = pow(max(dot(n, h), 0.0), mat_shininess);

        vec3 ambient = light_color_ambient[i] * color_ambient;
        vec3 diffuse = light_color_diffuse[i] * color_diffuse * reflection_diffuse;
        vec3 specular = light_color_specular[i] * color_specular * reflection_specular;
        final_ambient += ambient * attenuation;
        final_diffuse += diffuse * reflection_diffuse * attenuation;
        final_specular += specular * reflection_specular * attenuation;
    }

    vec3 final_color = (final_ambient + final_diffuse + final_specular) * texture_color.rgb;
    fragment_color = vec4(final_color, 1.0);

}