// Version d'OpenGL
#version 150

// Donnees d'entree
in vec3 in_position;
in vec4 in_color;

// Donnees de sortie
out vec4 out_color;

// Parametres
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// Fonction appellee pour chaque sommet
void main()
{
  // Affectation de la position du sommet
  // gl_Position est definit par defaut dan GLSL
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);

  //out_color = vec4((in_position + vec3(1,1,1))*0.5, 1.0);
  out_color = in_color;
}
