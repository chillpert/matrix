#version 460 core
out vec4 FragColor;

in VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
} fs_in;

struct Light
{
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
  float ambientStrength;
};

struct Material
{
  sampler2D diffuse_texture1;
  sampler2D specular_texture1;
  sampler2D normal_texture1;
  sampler2D height_texture1;

  float shininess;
};

uniform vec3 viewPosition;
uniform Light light;
uniform Material material;

void main()
{
  vec3 color = texture(material.diffuse_texture1, fs_in.TexCoords).rgb;
  // ambient
  vec3 ambient = light.ambientStrength * color * light.ambient;
  // diffuse
  vec3 normal = fs_in.Normal;
  vec3 lightDir = normalize(light.position - fs_in.FragPos);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = diff * light.diffuse;

  vec3 result = (ambient + diffuse) * color;
  FragColor = vec4(result, 1.0);
}

