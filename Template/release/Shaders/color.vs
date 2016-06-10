#version 330

uniform mat4 MVP;
// uniform vec3 cameraRight;
// uniform vec3 cameraUp;
// uniform mat4 ViewProj;

//in vec3 position;
in vec3 color;
in vec2 uv;
in vec3 renderVertice;

out vec3 fColor;
out vec2 fuv;

void main()
{
  //float particleSize = position.w; //Taille de la particule.
  //vec3 particleCenter = position.xyz; //Centre de la particule.
  
  //On se met au niveau du centre de la particule puis on s'oriente face
  //à la caméra à la bonne taille
  //vec3 vertexPosition = 
  //    particleCenter 
  //    + cameraRight * renderVertice.x * particleSize 
  //    + cameraUp * renderVertice.y * particleSize;
  
  gl_Position = MVP * vec4( renderVertice, 1.0f );
  
  fuv = uv;
  fColor = color;
}
