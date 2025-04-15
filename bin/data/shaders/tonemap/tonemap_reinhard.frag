#version 330

in vec2 surface_texcoord;
uniform sampler2D tex0;
uniform float exposure;
uniform float gamma;
out vec4 fragment_color;

void main()
{
    vec3 color;

  // échantillonner la texture
  vec3 texture_sample = texture(tex0, surface_texcoord).rgb;

  // valeur initiale de la couleur
  color = texture_sample;

  // conversion de la couleur de l'espace gamma vers l'espace linéaire
  color = pow(color, vec3(gamma));

  // ajustement de l'exposition
  color = vec3(1.0) - exp(-color * exposure);

  color = color / (color + vec3(1.0));

  // conversion de couleur de l'espace linéaire vers l'espace gamma
  color = pow(color, vec3(1.0 / gamma));

  // couleur du fragment
  fragment_color = vec4(color, 1.0);
}