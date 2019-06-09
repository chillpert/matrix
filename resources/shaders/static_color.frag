#version 460 core
out vec4 FragColor;

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
} fs_in;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 viewPos;

void main()
{
  FragColor = vec4(ambientColor.xyz, 1.0);
}
