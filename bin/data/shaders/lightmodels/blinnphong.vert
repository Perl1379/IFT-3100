#version 330

in vec4 position;
in vec4 normal;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;

out vec3 surface_position;
out vec3 surface_normal;
out vec2 surface_texcoord;
out mat3 TBN;       // Tangent, Bitangent, Normal matrix for fragment shader

uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

void main()
{
    mat4x4 normalMatrix = transpose(inverse(modelViewMatrix));
    surface_normal = vec3(normalMatrix * normal);
    surface_position = vec3(modelViewMatrix * position);
    surface_texcoord = texcoord;
    TBN = mat3(tangent, bitangent, surface_normal);

    gl_Position = projectionMatrix * modelViewMatrix * position;
}
