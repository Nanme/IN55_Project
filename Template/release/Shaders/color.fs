#version 330

in vec3 fColor;
in vec2 fuv;

out vec4 fragColor;

uniform sampler2D mytexture;

void main()
{
  fragColor = texture2D(mytexture, fuv).rgba;
  //fragColor = vec4(fColor,1.0f);
}
