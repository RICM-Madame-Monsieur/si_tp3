// Version d'OpenGL
#version 150

// Données d'entrée
in vec4 out_color;

// Données de sortie
out vec4 frag_color;

// Fonction appellee pour chaque fragment
void main()
{
  // Affectation de la couleur du fragment
  frag_color = vec4(out_color.rgb ,1.0);
}
