#version 420

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
uniform float pbr_metallic;
uniform float pbr_ior;
uniform float pbr_roughness;

uniform float texture_albedo_scale;
uniform float texture_normal_scale;

layout(binding=0) uniform sampler2D texture_albedo;
layout(binding=1) uniform sampler2D texture_normal;
layout(binding=2) uniform sampler2D texture_occlusion;
layout(binding=3) uniform sampler2D texture_roughness;
layout(binding=4) uniform sampler2D texture_metallic;


// Constants

const float PI = 3.1415926535897932384626433832795;


// fonction de distribution des microfacettes (Trowbridge-Reitz)
float trowbridge_reitz(vec3 n, vec3 h, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float ndh = max(dot(n, h), 0.0);
    float ndh2 = ndh * ndh;
    float numerator = a2;
    float denominator = (ndh2 * (a2 - 1.0) + 1.0);
    denominator = denominator * denominator * PI;
    return numerator / denominator;
}

// fonction géométrique pour calculer l'impact de l'occlusion et de l'ombrage des microfacettes (Schlick-Beckmann)
float schlick_beckmann(float costheta, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    float numerator = costheta;
    float denominator = costheta * (1.0 - k) + k;
    return numerator / denominator;
}

// fonction géométrique avec occlusion et ombrage combinés (méthode de Smith)
float smith(vec3 n, vec3 l, vec3 v, float roughness)
{
    float ndl = max(dot(n, l), 0.0);
    float ndv = max(dot(n, v), 0.0);
    float shadow = schlick_beckmann(ndl, roughness);
    float occlusion = schlick_beckmann(ndv, roughness);
    return shadow * occlusion;
}

// fonction qui calcul l'effet de Fresnel
vec3 schlick_fresnel(float costheta, vec3 f0)
{
    return f0 + (1.0 - f0) * pow(1.0 - costheta, 5.0);
}

// mappage tonal de la couleur HDR vers LDR (Reinhard tone mapping)
vec3 tone_mapping_reinhard(vec3 x)
{
    return x / (x + vec3(1.0));
}

// mappage tonal de la couleur HDR vers LDR (approximation de la courbe du ACES filmic tone mapping)
vec3 tone_mapping_aces_filmic(vec3 x)
{
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

// fonction qui calcule un modèle d'illumination de type pbr avec brdf de cook-torrance
vec3 brdf_cook_torrance()
{
    vec3 normal_color = texture(texture_normal, surface_texcoord * texture_normal_scale).rgb * 2.0 - 1.0;
    vec3 perturbed_normal = normalize(vec3(
                                      surface_normal.x + normal_color.x * 0.3,
                                      surface_normal.y + normal_color.y * 0.3,
                                      surface_normal.z
                                      ));

    vec3 n = perturbed_normal;

    // direction vers la caméra
    vec3 v = normalize(-surface_position);

    // échantillons de textures
    vec3 texture_sample_diffuse = texture(texture_albedo, surface_texcoord * texture_albedo_scale).rgb;
    float texture_sample_metallic = texture(texture_metallic, surface_texcoord).r;
    float texture_sample_roughness = texture(texture_roughness, surface_texcoord).r;
    float texture_sample_occlusion = texture(texture_occlusion, surface_texcoord).r;

    // propriétés du matériau
    float metallic = pbr_metallic * texture_sample_metallic;
    float roughness = pbr_roughness * texture_sample_roughness;
    float occlusion = texture_sample_occlusion;

    vec3 albedo = color_diffuse * texture_sample_diffuse;
    vec3 ambient = color_ambient * albedo * occlusion;

    // réflexion à incidence nulle

    float dielectric_ior = pbr_ior;
    float base_reflectivity = pow((dielectric_ior - 1.0) / (dielectric_ior + 1.0), 2.0);

    vec3 f0 = vec3(base_reflectivity);
    f0 = mix(f0, albedo, metallic);


    // accumulation des réflexions
    vec3 reflectance = vec3(0.0);

    for (int i = 0; i < light_sources; ++i)
    {
        vec3 l = normalize(light_position[i] - surface_position);
        vec3 h = normalize(l + v);
        float light_distance = length(light_position[i] - surface_position);
        float attenuation = 1.0 / (0.1 + light_attenuation[i] * light_distance);
        vec3 radiance = light_color_diffuse[i] * attenuation;

        float n_dot_l = max(dot(n, l), 0.0);

        float d = trowbridge_reitz(n, h, roughness);
        float g = smith(n, l, v, roughness);
        vec3 f = schlick_fresnel(max(dot(h, v), 0.0), f0);

        vec3 numerator = d * f * g;
        float denominator = 4.0 * max(dot(n, v), 0.0) * n_dot_l;
        vec3 specular = numerator / max(denominator, 0.001);

        vec3 ks = f;
        vec3 kd = vec3(1.0) - ks;
        kd *= 1.0 - metallic;

        reflectance += (kd * albedo / PI + specular) * radiance * n_dot_l;
    }

    vec3 color = global_ambient_color + ambient + reflectance;
    return color;
}

void main()
{
    // évaluation du modèle d'illumination
    vec3 color = brdf_cook_torrance();

    // assigner la couleur final du fragment dans un attribut en sortie
    fragment_color = vec4(color, 1.0);
}
