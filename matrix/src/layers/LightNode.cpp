#include <LightNode.h>

namespace MX
{
  std::string light_type = "UNDEF";

  LightNode::LightNode(const std::string &name)
    : Node(name) { }

  void LightNode::upload_uniforms(u_short index)
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

  DirectionalLightNode::DirectionalLightNode(const std::string &name)
    : LightNode(name) { }

  void DirectionalLightNode::upload_uniforms(u_short index)
  {
    light_type = "dir_lights";
    std::string index_s = std::to_string(index);

    LightNode::upload_uniforms(index);

    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".direction", direction);
  }

  PointLightNode::PointLightNode(const std::string &name)
    : LightNode(name) { }

  void PointLightNode::upload_uniforms(u_short index)
  {
    light_type = "point_lights";
    std::string index_s = std::to_string(index);

    LightNode::upload_uniforms(index);

    m_Shader->setfVec3(light_type + "[" + index_s + "]" + ".position", position);

    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".constant", constant);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".linear", linear);
    m_Shader->setFloat(light_type + "[" + index_s + "]" + ".quadratic", quadratic);
  }

  SpotLightNode::SpotLightNode(const std::string &name)
    : LightNode(name) { }

  void SpotLightNode::upload_uniforms(u_short index)
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
}