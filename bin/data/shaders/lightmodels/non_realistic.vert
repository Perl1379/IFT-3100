#version 330 core

in vec4 position;
in vec4 normal;
in vec2 texcoord;

out vec3 surface_position;
out vec3 surface_normal;
out vec2 surface_texcoord;

// Uniforms
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    // Compute normal matrix (transpose of inverse of modelViewMatrix)
    mat4 normalMatrix = transpose(inverse(modelViewMatrix));

    // Transform the normal and ensure it's normalized
    surface_normal = normalize(vec3(normalMatrix * normal));

    // Transform the position to view space (camera space)
    surface_position = vec3(modelViewMatrix * position);

    // Pass through texture coordinates
    surface_texcoord = texcoord;

    gl_Position = projectionMatrix * modelViewMatrix * position;
}
