#ifndef MODEL_H
#define MODEL_H

#ifdef MX_OPENGL_ACTIVE
  #define MX_MODEL MX::Model_OpenGL
#elif MX_DIRECTX_ACTIVE
  #define MX_MODEL MX::Model_DirectX
#endif

#include <stdafx.h>

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
    MX_API Model() = default;
    MX_API ~Model() = default;

    MX_API Model(const Model&) = default;
    MX_API Model &operator=(const Model&) = default;

    MX_API virtual void initialize() = 0;
    MX_API virtual void draw() = 0;
    MX_API virtual void setGeometry(u_int64_t draw_mode) = 0;
    
    MX_API std::string getName() const { return m_Name; }

    std::string m_Name;
    std::string m_Path;

    std::vector<Material*> m_MaterialList;
    std::vector<glm::vec3> m_V;
    std::vector<glm::vec2> m_Vt;
    std::vector<glm::vec3> m_Vn;

    bool m_initialized = 0;
  };
}

#endif // MODEL_H