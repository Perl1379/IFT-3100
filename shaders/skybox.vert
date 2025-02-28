#version 150

in vec3 position;  // Position of the vertex (the cube's vertices)
out vec3 texCoord; // The texture coordinates that will be passed to the fragment shader

uniform mat4 modelViewProjectionMatrix; // Model-view-projection matrix

void main() {
    texCoord = position; // In a cubemap, the texture coordinates are the same as the vertex positions
    gl_Position = modelViewProjectionMatrix * vec4(position, 1.0);
}