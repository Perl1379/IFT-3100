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

    mat4 normalMatrix = transpose(inverse(modelViewMatrix));
    surface_normal = normalize(vec3(normalMatrix * normal));
    surface_position = vec3(modelViewMatrix * position);
    surface_texcoord = texcoord;

    gl_Position = projectionMatrix * modelViewMatrix * position;
}
