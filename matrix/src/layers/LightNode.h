#ifndef LIGHTNODE_H
#define LIGHTNODE_H

#include "Node.h"

namespace MX
{
  extern std::string light_type;

  class LightNode;
  class DirectionalLightNode;
  class PointLightNode;
  class SpotLightNode;

  typedef LightNode* MX_LightNode;
  typedef DirectionalLightNode* MX_DirectionalLightNode;
  typedef PointLightNode* MX_PointLightNode;
  typedef SpotLightNode* MX_SpotLightNode;

  class LightNode : public Node
  {
  public:
    MX_API LightNode() = delete;
    MX_API LightNode(const std::string &name, const NodeType& type = type_light);
    MX_API virtual ~LightNode() = default;

    MX_API LightNode(const LightNode&) = default;
    MX_API LightNode &operator=(const LightNode&) = default;

    MX_API virtual LightNode* getNode() { return this; }

    MX_API virtual std::string getIdentifier() = 0;

    MX_API virtual void upload_uniforms(unsigned short index);

    MX_API virtual std::string to_string() const;

    glm::vec3 ambient = glm::fvec3(0.2f, 0.2f, 0.2f);
    glm::vec3 diffuse = glm::fvec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::fvec3(1.0f, 1.0f, 1.0f);

    float ambient_strength = 0.7f;
  };

  class DirectionalLightNode : public LightNode
  {
  public:
    MX_API DirectionalLightNode() = delete;
    MX_API DirectionalLightNode(const std::string &name);

    MX_API DirectionalLightNode* getNode() { return this; }

    MX_API std::string getIdentifier() { return "Directional Light"; }

    MX_API void upload_uniforms(unsigned short index) override;

    MX_API virtual std::string to_string() const;
  
  public:
    glm::vec3 direction = glm::vec3(1.0f, -1.0f, -1.0f);
  };

  class PointLightNode : public LightNode
  {
  public:
    MX_API PointLightNode() = delete;
    MX_API PointLightNode(const std::string &name);

    MX_API PointLightNode* getNode() { return this; }

    MX_API std::string getIdentifier() { return "Point Light"; }

    MX_API void upload_uniforms(unsigned short index) override;

    MX_API virtual std::string to_string() const;

  public:
    glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f);

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
  };

  class SpotLightNode : public LightNode
  {
  public:
    MX_API SpotLightNode() = default;
    MX_API SpotLightNode(const std::string &name);

    MX_API SpotLightNode* getNode() { return this; }

    MX_API std::string getIdentifier() { return "Spot Light"; }

    MX_API void upload_uniforms(unsigned short index) override;

    MX_API virtual std::string to_string() const;

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