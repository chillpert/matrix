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
uniform float ambientStrength;

void main()
{           
  vec3 color = texture(texture1, fs_in.TexCoords).rgb;
  // ambient
  vec3 ambient = ambientStrength * color * lightColor;
  // diffuse
  vec3 normal = fs_in.Normal;
  vec3 lightDir = normalize(lightPosition - fs_in.FragPos);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * color;
  FragColor = vec4(result, 1.0);
}

