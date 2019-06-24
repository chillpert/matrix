#ifndef LIGHTNODE_H
#define LIGHTNODE_H

#include <Node.h>

namespace MX
{
  extern std::string light_type;

  class LightNode : public Node
  {
  public:
    MX_API LightNode() = delete;
    MX_API LightNode(const std::string &name);
    MX_API virtual ~LightNode() = default;

    MX_API LightNode(const LightNode&) = default;
    MX_API LightNode &operator=(const LightNode&) = default;

    MX_API virtual std::string getIdentifier() = 0;

    MX_API virtual void upload_uniforms(u_short index);

    glm::vec3 ambient = glm::fvec3(0.1f, 0.1f, 0.1f);
    glm::vec3 diffuse = glm::fvec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::fvec3(1.0f, 1.0f, 1.0f);

    float ambient_strength = 0.08f;
  };

  class DirectionalLightNode : public LightNode
  {
  public:
    MX_API DirectionalLightNode() = delete;
    MX_API DirectionalLightNode(const std::string &name);

    MX_API std::string getIdentifier() { return "Directional Light"; }

    void upload_uniforms(u_short index) override;
  
  public:
    glm::vec3 direction = glm::vec3(1.0f, -1.0f, -1.0f);
  };

  class PointLightNode : public LightNode
  {
  public:
    MX_API PointLightNode() = delete;
    MX_API PointLightNode(const std::string &name);

    MX_API std::string getIdentifier() { return "Point Light"; }

    void upload_uniforms(u_short index) override;

  public:
    glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f);

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
  };

  class SpotLightNode : public LightNode
  {
  public:
    MX_API SpotLightNode() = delete;
    MX_API SpotLightNode(const std::string &name);

    MX_API std::string getIdentifier() { return "Spot Light"; }

    void upload_uniforms(u_short index) override;

  public:
    glm::vec3 position = glm::vec3(0.0f, 5.0f, 0.0f);
    glm::vec3 direction = glm::vec3(1.0f);

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    float cut_off = glm::cos(glm::radians(12.5f));
    float outer_cut_off = glm::cos(glm::radians(17.5f));
  };
}

#endif // LIGHTNODE_H