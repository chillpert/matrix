#ifndef MODEL_H
#define MODEL_H

#ifdef MX_OPENGL_ACTIVE
  #define MX_MODEL MX::Model_OpenGL
#elif MX_DIRECTX_ACTIVE
  #define MX_MODEL MX::Model_DirectX
#endif

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  struct RGB
  {
    float r;
    float g;
    float b;
  };

  struct Material
  {
    RGB m_Ambient;
    RGB m_Diffuse;
    RGB m_Specular;
    float m_Alpha;
    float m_Shininess;
    std::string m_TexturePath;
  };

  class Model
  {
  public:
    MX_API Model() {}
    MX_API ~Model() {}

    MX_API virtual void parse() = 0;
    MX_API virtual void draw() = 0;
    MX_API virtual void setGeometry(unsigned int draw_mode) = 0;
    
    MX_API std::string getName() const { return m_Name; }
    MX_API std::string getPath() const { return m_Path; }

    MX_API const std::vector<Material*> &getMaterialList() { return m_MaterialList; }
    MX_API std::vector<glm::vec3> &getV() { return m_V; }
    MX_API std::vector<glm::vec2> &getVt() { return m_Vt; }
    MX_API std::vector<glm::vec3> &getVn() { return m_Vn; }
  protected:
    std::string m_Name;
    std::string m_Path;

    std::vector<Material*> m_MaterialList;
    std::vector<glm::vec3> m_V;
    std::vector<glm::vec2> m_Vt;
    std::vector<glm::vec3> m_Vn;
  };
}

#endif // MODEL_H