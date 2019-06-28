#version 460 core
out vec4 FragColor;

in VS_OUT
{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
} fs_in;

struct DirLight
{
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float ambientStrength;

  float exists;
};

struct PointLight
{
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float ambientStrength;

  float constant;
  float linear;
  float quadratic;

  float exists;
};

struct SpotLight
{
  vec3 position;
  vec3 direction;

  float cutOff;
  float outerCutOff;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float ambientStrength;

  float constant;
  float linear;
  float quadratic;

  float exists;
};

struct Material
{
  // do not have an ambient texture since that is in 99% of all cases identical to diffuse
  sampler2D diffuse_texture1;
  sampler2D specular_texture1;
  sampler2D normal_texture1;
  sampler2D bump_texture1;
  sampler2D height_texture1;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float shininess;
};

uniform vec3 viewPosition;

uniform Material material;

#define NR_DIR_LIGHTS 5
#define NR_POINT_LIGHTS 5
#define NR_SPOT_LIGHTS 5

uniform DirLight dir_lights[NR_DIR_LIGHTS];
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight spot_lights[NR_SPOT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
  vec3 norm = fs_in.Normal;
  vec3 fragPos = fs_in.FragPos;
  vec3 viewDir = normalize(viewPosition - fs_in.FragPos);

  vec3 result;

  for (int i = 0; i < NR_DIR_LIGHTS; ++i)
    result += CalcDirLight(dir_lights[i], norm, fragPos, viewDir);

  for (int i = 0; i < NR_POINT_LIGHTS; ++i)
    result += CalcPointLight(point_lights[i], norm, fragPos, viewDir);

  for (int i = 0; i < NR_SPOT_LIGHTS; ++i)
    result += CalcSpotLight(spot_lights[i], norm, fragPos, viewDir);

  FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  if (light.exists == 0.0)
    return vec3(0.0, 0.0, 0.0);

  // ambient
  vec3 ambient = light.ambientStrength * light.ambient * texture(material.diffuse_texture1, fs_in.TexCoords).rgb * material.ambient;

  // diffuse
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = light.diffuse * (diff * texture(material.diffuse_texture1, fs_in.TexCoords).rgb * material.diffuse);

  // specular
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
  vec3 specular = light.specular * (spec * texture(material.specular_texture1, fs_in.TexCoords).rgb * material.specular);

  return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  if (light.exists == 0.0)
    return vec3(0.0, 0.0, 0.0);

  // ambient
  vec3 ambient = light.ambientStrength * light.ambient * texture(material.diffuse_texture1, fs_in.TexCoords).rgb * material.ambient;

  // diffuse
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = light.diffuse * (diff * texture(material.diffuse_texture1, fs_in.TexCoords).rgb * material.diffuse);

  // specular
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
  vec3 specular = light.specular * (spec * texture(material.specular_texture1, fs_in.TexCoords).rgb * material.specular);

  // attenuation
  float distance    = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  if (light.exists == 0.0)
    return vec3(0.0, 0.0, 0.0);

  // ambient
  vec3 ambient = light.ambientStrength * light.ambient * texture(material.diffuse_texture1, fs_in.TexCoords).rgb * material.ambient;

  // diffuse
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = light.diffuse * (diff * texture(material.diffuse_texture1, fs_in.TexCoords).rgb * material.diffuse);

  // specular
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
  vec3 specular = light.specular * (spec * texture(material.specular_texture1, fs_in.TexCoords).rgb * material.specular);

  // spotlight (soft edges)
  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = (light.cutOff - light.outerCutOff);
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
  diffuse  *= intensity;
  specular *= intensity;

  // attenuation
  float distance    = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}