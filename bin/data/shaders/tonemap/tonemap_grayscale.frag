#version 330

in vec2 surface_texcoord;
uniform sampler2D tex0;
uniform float brightness; // Add this uniform
out vec4 fragment_color;

void main()
{
  vec4 color = texture(tex0, surface_texcoord);

  // Use luminance
  float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
  gray *= brightness; // Adjust brightness
  fragment_color = vec4(vec3(gray), color.a);
}
