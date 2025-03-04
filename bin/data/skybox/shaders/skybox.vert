#version 330 core

layout(location = 0) in vec3 position; // Position of the vertex (the cube's vertices)
out vec3 texCoord; // The texture coordinates to pass to the fragment shader

uniform mat4 modelViewProjectionMatrix; // Model-view-projection matrix

void main() {
    // Pass the vertex position as the texture coordinates
    texCoord = position; // Cubemap uses the vertex positions as texture coordinates

    // Apply the model-view-projection matrix to the vertex
    gl_Position = modelViewProjectionMatrix * vec4(position, 1.0);
}
