// IFT3100H24 ~ tone_mapping_330_vs.glsl

#version 330

// attribut uniforme
uniform mat4 modelViewProjectionMatrix;

// attributs de sommet
in vec4 position;
in vec2 texcoord;

// attribut en sortie
out vec2 surface_texcoord;

void main()
{
  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = modelViewProjectionMatrix * position;
}
