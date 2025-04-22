#version 150

in vec3 surface_position;
in vec3 surface_normal;
in vec2 surface_texcoord;
in vec3 normal_tangent;
in vec3 normal_bitangent;

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
uniform float texture_normal_scale;

uniform sampler2D textureAlbedo;
uniform sampler2D textureNormal;

const float material_roughness = 0.5;
const float material_metallic = 0.0;

// Constants
const float PI = 3.14159265359;

vec3 getNormal()
{
    vec3 n = normalize(surface_normal);
    if (texture_normal_scale > 0.0) {
        vec3 normal_map = texture(textureNormal, surface_texcoord).rgb;
        normal_map = normalize(normal_map * 2.0 - 1.0);
        mat3 TBN = mat3(normalize(normal_tangent), normalize(normal_bitangent), normalize(n));
        n = normalize(TBN * normal_map);
    }
    return n;
}

float distributionGGX(vec3 n, vec3 h, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float ndh = max(dot(n, h), 0.0);
    float denom = (ndh * ndh * (a2 - 1.0) + 1.0);
    return a2 / (PI * denom * denom);
}

float geometrySchlickGGX(float ndv, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    return ndv / (ndv * (1.0 - k) + k);
}

float geometrySmith(vec3 n, vec3 v, vec3 l, float roughness)
{
    float ndv = max(dot(n, v), 0.0);
    float ndl = max(dot(n, l), 0.0);
    float ggx1 = geometrySchlickGGX(ndv, roughness);
    float ggx2 = geometrySchlickGGX(ndl, roughness);
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cos_theta, vec3 f0)
{
    return f0 + (1.0 - f0) * pow(1.0 - cos_theta, 5.0);
}

void main()
{
    vec3 n = getNormal();
    vec3 v = normalize(-surface_position); // camera is at (0,0,0)

    // Albedo (color_diffuse or texture)
    vec3 tex_albedo = pow(texture(textureAlbedo, surface_texcoord).rgb, vec3(2.2));
    vec3 albedo = mix(color_diffuse, tex_albedo, texture_albedo_scale);

    // Fresnel reflectance at normal incidence
    vec3 f0 = mix(vec3(0.04), albedo, material_metallic);

    vec3 radiance_total = vec3(0.0);

    for (int i = 0; i < light_sources; ++i)
    {
        vec3 l;
        float attenuation = 1.0;
        if (light_type[i] == 0) { // point
            vec3 lp = light_position[i];
            vec3 light_vec = lp - surface_position;
            float d = length(light_vec);
            l = normalize(light_vec);
            attenuation = 1.0 / (1.0 + light_attenuation[i] * d * d);
        }
        else if (light_type[i] == 1) { // directional
            l = normalize(-light_orientation[i]);
        }
        else {
            continue; // skip unsupported light types
        }

        vec3 h = normalize(v + l);
        float ndl = max(dot(n, l), 0.0);
        float ndv = max(dot(n, v), 0.0);
        float ndh = max(dot(n, h), 0.0);

        // Cook-Torrance BRDF
        float D = distributionGGX(n, h, material_roughness);
        float G = geometrySmith(n, v, l, material_roughness);
        vec3 F = fresnelSchlick(max(dot(h, v), 0.0), f0);

        vec3 specular = (D * G * F) / max(4.0 * ndv * ndl, 0.001);

        vec3 kS = F;
        vec3 kD = (vec3(1.0) - kS) * (1.0 - material_metallic);

        vec3 light_color = light_color_diffuse[i];
        vec3 light_radiance = light_color * attenuation;

        radiance_total += (kD * albedo / PI + specular) * light_radiance * ndl;
    }

    // Ambient term
    vec3 ambient = (global_ambient_color + color_ambient) * albedo * (1.0 - material_metallic);

    // Final color
    vec3 color = ambient + radiance_total;

    // Tone mapping and gamma correction
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0 / 2.2)); // gamma correction

    fragment_color = vec4(color, 1.0);
}
