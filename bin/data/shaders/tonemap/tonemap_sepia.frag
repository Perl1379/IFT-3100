#version 330

in vec2 surface_texcoord;
uniform sampler2D tex0;
uniform float brightness; // Add this uniform
out vec4 fragment_color;

void main()
{
    vec4 color = texture(tex0, surface_texcoord);
    
    vec3 lum = vec3(0.299, 0.587, 0.114);
    float sepia = dot(color.rgb, lum);
    sepia *= brightness;
    fragment_color = vec4( sepia * vec3( 1.0, 0.8, 0.4), color.a);
}
