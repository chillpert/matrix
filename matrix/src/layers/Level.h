#ifndef LEVEL_H
#define LEVEL_H

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/layers/SceneGraph.h"

#include "matrix/src/platform/api/Model.h"
#include "matrix/src/platform/api/Shader.h"
#ifdef MX_OPENGL_ACTIVE
  #include "matrix/src/platform/api/Model_OpenGL.h"
  #include "matrix/src/platform/api/Shader_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
  #include "matrix/src/platform/api/Shader_DirectX.h"
#endif

namespace MX
{
  class Level 
  {
  public:
    MX_API Level() {}
    MX_API Level(const std::string &name)
      : m_Name(name) {}
    MX_API ~Level() {}

    MX_API void initialize();
    MX_API void update();
    MX_API void render();
    
    template <typename T>
    void push(T obj);

    template <typename T>
    T &find(const std::string &name);
  private:
    SceneGraph m_SG;

    MX_MODEL m;
    MX_SHADER s;
  public:
    std::string m_Name;
  };
}

#endif // LEVEL_H