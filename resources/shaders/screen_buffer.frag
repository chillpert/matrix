#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform bool inverse_color;
uniform bool depth_map;
uniform bool shadow_map;

uniform float near_plane;
uniform float far_plane;

uniform sampler2D screen_texture;
uniform sampler2D depth_texture;

float linearize_depth(float depth)
{
  float z = depth * 2.0 - 1.0; // Back to NDC 
  return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

void main()
{
  if (depth_map || shadow_map)
  {
    float depth_value = texture(depth_texture, TexCoords).r;

    if (inverse_color)
      FragColor = vec4(1 - vec3(depth_value), 1.0);
    else
      FragColor = vec4(vec3(depth_value), 1.0);
  }
  else if (inverse_color)
  {
    FragColor += vec4(vec3(1.0 - texture(screen_texture, TexCoords)), 1.0);
  }
  else
  {
    FragColor += vec4(vec3(texture(screen_texture, TexCoords)), 1.0);
  }

} 

