#version 150

in vec3 texCoord;
out vec4 fragColor;

uniform sampler2D Tex0;
uniform sampler2D Tex1;
uniform sampler2D Tex2;
uniform sampler2D Tex3;
uniform sampler2D Tex4;
uniform sampler2D Tex5;

vec2 adjustTexCoord(vec2 coord) {
    coord = (coord * 0.5) + 0.5;
    coord.x = 1 - coord.x;
    return coord;
}

void main() {
    vec3 dir = normalize(texCoord);

    if (abs(dir.x) > abs(dir.y) && abs(dir.x) > abs(dir.z)) {
        if (dir.x > 0.0) {
            // Right face (Tex0)
            fragColor = texture(Tex0, adjustTexCoord(vec2(-dir.z / dir.x, -dir.y / dir.x)));
        } else {
            // Left face (Tex1)
            fragColor = texture(Tex1, adjustTexCoord(vec2(dir.z / -dir.x, -dir.y / -dir.x)));
        }
    } else if (abs(dir.y) > abs(dir.x) && abs(dir.y) > abs(dir.z)) {
        if (dir.y > 0.0) {
            // Top face (Tex2)
            fragColor = texture(Tex2, adjustTexCoord(vec2(dir.x / dir.y, dir.z / dir.y)));
        } else {
            // Bottom face (Tex3)
            fragColor = texture(Tex3, adjustTexCoord(vec2(dir.x / -dir.y, -dir.z / -dir.y)));
        }
    } else {
        if (dir.z > 0.0) {
            // Front face (Tex4)
            fragColor = texture(Tex4, adjustTexCoord(vec2(dir.x / dir.z, -dir.y / dir.z)));
        } else {
            // Back face (Tex5)
            fragColor = texture(Tex5, adjustTexCoord(vec2(-dir.x / -dir.z, -dir.y / -dir.z)));
        }
    }
}