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
    
    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".ambient", m_ambient);
    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".diffuse", m_diffuse);
    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".specular", m_specular);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".ambientStrength", m_ambient_strength);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".exists", 1.0);
  }

  std::string LightNode::to_string() const
  {
    std::stringstream ss;
    ss << Node::to_string();

    ss << "\n@Ambient{" << glm::to_string(m_ambient) << "}";
    ss << "\n@Diffuse{" << glm::to_string(m_diffuse) << "}";
    ss << "\n@Specular{" << glm::to_string(m_specular) << "}";
    ss << "\n@Strength{" << std::to_string(m_ambient_strength) << "}\n-";

    return ss.str();
  }

  DirectionalLightNode::DirectionalLightNode(const std::string &name)
    : LightNode(name, NodeType::type_directionalLight) { }

  void DirectionalLightNode::upload_uniforms(unsigned short index)
  {
    light_type = "dir_lights";
    std::string index_s = std::to_string(index);

    LightNode::upload_uniforms(index);

    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".direction", m_direction);
  }

  std::string DirectionalLightNode::to_string() const
  {
    std::stringstream ss;
    ss << LightNode::to_string();

    ss << "\n@DirectionalDirection{" << glm::to_string(m_direction) << "}\n-";

    return ss.str();
  }

  PointLightNode::PointLightNode(const std::string &name)
    : LightNode(name, NodeType::type_pointLight) { }

  void PointLightNode::upload_uniforms(unsigned short index)
  {
    light_type = "point_lights";
    std::string index_s = std::to_string(index);

    LightNode::upload_uniforms(index);

    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".position", m_position);

    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".constant", m_constant);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".linear", m_linear);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".quadratic", m_quadratic);
  }

  std::string PointLightNode::to_string() const
  {
    std::stringstream ss;
    ss << LightNode::to_string();

    ss << "\n@PointPosition{" << glm::to_string(m_position) << "}";
    ss << "\n@PointConstant{" << std::to_string(m_constant) << "}";
    ss << "\n@PointLinear{" << std::to_string(m_linear) << "}";
    ss << "\n@PointQuadratic{" << std::to_string(m_quadratic) << "}\n-";

    return ss.str();
  }

  SpotLightNode::SpotLightNode(const std::string &name)
    : LightNode(name, NodeType::type_spotLight) { }

  void SpotLightNode::upload_uniforms(unsigned short index)
  {
    light_type = "spot_lights";
    std::string index_s = std::to_string(index);

    LightNode::upload_uniforms(index);

    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".position", m_position);
    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".direction", m_direction);

    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".constant", m_constant);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".linear", m_linear);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".quadratic", m_quadratic);

    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".cutOff", m_cut_off);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".outerCutOff", m_outer_cut_off);
  }

  std::string SpotLightNode::to_string() const
  {
    std::stringstream ss;
    ss << LightNode::to_string();

    ss << "\n@SpotPosition{" << glm::to_string(m_position) << "}";
    ss << "\n@SpotDirection{" << glm::to_string(m_direction) << "}";
    ss << "\n@SpotConstant{" << std::to_string(m_constant) << "}";
    ss << "\n@SpotLinear{" << std::to_string(m_linear) << "}";
    ss << "\n@SpotQuadratic{" << std::to_string(m_quadratic) << "}";
    ss << "\n@CutOff{" << std::to_string(m_cut_off) << "}";
    ss << "\n@OuterCutOff{" << std::to_string(m_outer_cut_off) << "}\n-";

    return ss.str();
  }
}