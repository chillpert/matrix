#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screen_texture;

void main()
{
  // inversion
  FragColor = vec4(vec3(1.0 - texture(screen_texture, TexCoords)), 1.0);
} 

