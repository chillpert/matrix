#include "LightNode.h"

namespace MX
{
  std::string light_type = "UNDEF";

  LightNode::LightNode(const std::string &name, const NodeType& type)
    : Node(name, type) { }

  void LightNode::upload_uniforms(unsigned short index)
  {
    if (light_type == "UNDEF")
      MX_FATAL("MX: Node: LightNode: Uniform upload is UNDEF");

    std::string index_s = std::to_string(index);

    m_Shader->use();
    
    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".ambient", ambient);
    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".diffuse", diffuse);
    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".specular", specular);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".ambientStrength", ambient_strength);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".exists", 1.0);
  }

  std::string LightNode::to_string() const
  {
    std::stringstream ss;
    ss << Node::to_string();

    ss << "\n@Ambient{" << glm::to_string(ambient) << "} ";
    ss << "\n@Diffuse{" << glm::to_string(diffuse) << "} ";
    ss << "\n@Specular{" << glm::to_string(specular) << "} ";
    ss << "\n@AmbientStrength{" << std::to_string(ambient_strength) << "}\n";

    return ss.str();
  }

  DirectionalLightNode::DirectionalLightNode(const std::string &name)
    : LightNode(name, NodeType::type_directionalLight) { }

  void DirectionalLightNode::upload_uniforms(unsigned short index)
  {
    light_type = "dir_lights";
    std::string index_s = std::to_string(index);

    LightNode::upload_uniforms(index);

    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".direction", direction);
  }

  std::string DirectionalLightNode::to_string() const
  {
    std::stringstream ss;
    ss << LightNode::to_string();

    ss << "\n@Direction{" << glm::to_string(direction) << "}\n";

    return ss.str();
  }

  PointLightNode::PointLightNode(const std::string &name)
    : LightNode(name, NodeType::type_pointLight) { }

  void PointLightNode::upload_uniforms(unsigned short index)
  {
    light_type = "point_lights";
    std::string index_s = std::to_string(index);

    LightNode::upload_uniforms(index);

    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".position", position);

    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".constant", constant);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".linear", linear);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".quadratic", quadratic);
  }

  std::string PointLightNode::to_string() const
  {
    std::stringstream ss;
    ss << LightNode::to_string();

    ss << "\n@Position{" << glm::to_string(position) << "} ";
    ss << "\n@Constant{" << std::to_string(constant) << "} ";
    ss << "\n@Linear{" << std::to_string(linear) << "} ";
    ss << "\n@Quadratic{" << std::to_string(quadratic) << "}\n";

    return ss.str();
  }

  SpotLightNode::SpotLightNode(const std::string &name)
    : LightNode(name, NodeType::type_spotLight) { }

  void SpotLightNode::upload_uniforms(unsigned short index)
  {
    light_type = "spot_lights";
    std::string index_s = std::to_string(index);

    LightNode::upload_uniforms(index);

    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".position", position);
    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".direction", direction);

    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".constant", constant);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".linear", linear);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".quadratic", quadratic);

    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".cutOff", cut_off);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".outerCutOff", outer_cut_off);
  }

  std::string SpotLightNode::to_string() const
  {
    std::stringstream ss;
    ss << LightNode::to_string();

    ss << "\n@Position{" << glm::to_string(position) << "} ";
    ss << "\n@Direction{" << glm::to_string(direction) << "} ";
    ss << "\n@Constant{" << std::to_string(constant) << "} ";
    ss << "\n@Linear{" << std::to_string(linear) << "} ";
    ss << "\n@Quadratic{" << std::to_string(quadratic) << "} ";
    ss << "\n@CutOff{" << std::to_string(cut_off) << "} ";
    ss << "\n@OuterCutOff{" << std::to_string(outer_cut_off) << "}\n";

    return ss.str();
  }
}