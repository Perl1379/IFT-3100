#version 330

in vec4 position;
in vec4 normal;
in vec2 texcoord;

out vec3 surface_color;
out vec2 surface_texcoord;

uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

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

void main()
{
    mat4x4 normalMatrix = transpose(inverse(modelViewMatrix));
    vec3 n = normalize(vec3(normalMatrix * normal));
    vec3 p = vec3(modelViewMatrix * position);

    vec3 final_ambient = global_ambient_color;
    vec3 final_diffuse = vec3(0.0);

    for (int i = 0; i < light_sources; ++i)
    {
        vec3 l;
        float attenuation = 1.0;

        // Lumière directionnelle
        if (light_type[i] == 2)
        {
            l = normalize(light_orientation[i]);
        }
        // Lumière ponctuelle
        else if (light_type[i] == 1)
        {
            l = normalize(light_position[i] - p);
            float dist = length(light_position[i] - p);
            attenuation = 1.0 / (0.1 + light_attenuation[i] * dist);
            attenuation = max(attenuation, 0.01);
        }
        // Projecteur
        else if (light_type[i] == 0)
        {
            l = normalize(light_position[i] - p);
            float spot_factor = dot(normalize(light_orientation[i]), -l);
            if (spot_factor < 0.0) {
                spot_factor = 0.0;
            }
            float dist = length(light_position[i] - p);
            attenuation = 1.0 / (0.1 + light_attenuation[i] * dist);
            attenuation = max(attenuation, 0.01);

            float spot_threshold = 0.9;
            spot_factor = smoothstep(spot_threshold, 1.0, spot_factor);
            attenuation *= spot_factor;
        }


        attenuation = max(attenuation, 0.01);

        float reflection_diffuse = max(dot(n, l), 0.0);

        vec3 ambient = light_color_ambient[i] * color_ambient;
        vec3 diffuse = light_color_diffuse[i] * color_diffuse * reflection_diffuse;
        final_ambient += ambient;
        final_diffuse += diffuse * reflection_diffuse * attenuation;
    }

    surface_color = final_ambient + final_diffuse;
    surface_texcoord = texcoord;
    
    gl_Position = projectionMatrix * modelViewMatrix * position;
}
