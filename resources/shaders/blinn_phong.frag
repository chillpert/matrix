#version 460 core
out vec4 FragColor;

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
} fs_in;

uniform sampler2D texture1;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform float ambientStrength;

void main()
{           
  vec3 color = texture(texture1, fs_in.TexCoords).rgb * lightColor;
  // ambient
  vec3 ambient = ambientStrength * color;
  // diffuse
  vec3 normal = fs_in.Normal;
  vec3 lightDir = normalize(lightPosition - fs_in.FragPos);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = diff * color;
  // specular
  vec3 viewDir = normalize(viewPosition - fs_in.FragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

  vec3 specular = vec3(0.3) * spec; // assuming bright white light color
  FragColor = vec4(ambient + diffuse + specular, 1.0);
}