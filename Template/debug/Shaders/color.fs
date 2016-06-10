#version 140


in vec3 fColor;
in vec2 fuv;

out vec3 fragColor;

uniform sampler2D texture;

void main()
{
  fragColor = texture2D(texture, fuv).rgb;
  //fragColor = vec4(fColor,1.0f);
}
