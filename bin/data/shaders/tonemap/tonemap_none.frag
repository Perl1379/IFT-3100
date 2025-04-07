// fragment shader
#version 330

in vec2 surface_texcoord;
uniform sampler2D tex0;
out vec4 fragment_color;

void main()
{
  fragment_color = texture(tex0, surface_texcoord);
}