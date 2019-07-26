#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform bool inverse_color;
uniform bool depth_map;
uniform bool shadow_map; 

uniform sampler2D screen_texture;

void main()
{
  if (inverse_color)
  {
    FragColor = vec4(vec3(1.0 - texture(screen_texture, TexCoords)), 1.0);
  }
  else
  {
    FragColor = vec4(vec3(texture(screen_texture, TexCoords)), 1.0);
  }

} 

