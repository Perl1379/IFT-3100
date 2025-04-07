#version 330 core
out vec4 FragColor;
in vec3 TexCoords;

uniform samplerCube skybox;

void main() {
    // Flip x-axis to correct mirroring issue
    FragColor = texture(skybox, vec3(-TexCoords.x, TexCoords.y, TexCoords.z));
}
