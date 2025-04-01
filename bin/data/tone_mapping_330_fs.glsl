// IFT3100H24 ~ tone_mapping_330_fs.glsl

#version 330

// attribut en sortie
out vec4 fragment_color;


// mappage tonal de la couleur hdr vers ldr (reinhard tone mapping)


void main()
{
  // variable qui va contenir la couleur à corriger
  
  fragment_color = vec4(1.0,0.0,0.0,1.0);
}
