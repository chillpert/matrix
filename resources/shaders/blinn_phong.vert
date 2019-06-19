#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
} vs_out;

void main()
{
  vs_out.FragPos = vec3(model * vec4(aPos, 1.0));;
  vs_out.Normal = normalize(mat3(transpose(inverse(model))) * aNormal);
  vs_out.TexCoords = aTexCoord;

  gl_Position = projection * view * model * vec4(aPos, 1.0);
}