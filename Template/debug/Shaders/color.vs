#version 140


uniform mat4 MVP;

in vec3 position;
in vec3 color;
in vec2 uv;

out vec3 fColor;
out vec2 fuv;

void main()
{
  gl_Position = MVP * vec4( position, 1.0f );
  
  fuv = uv;
  fColor = color;
}
