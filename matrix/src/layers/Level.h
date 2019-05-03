#ifndef LEVEL_H
#define LEVEL_H

#include "matrix/src/pch/stdafx.h"

#include "matrix/src/platform/api/Model.h"
#include "matrix/src/platform/api/Model_Handler.h"
#include "matrix/src/platform/api/Shader.h"
#ifdef MX_OPENGL_ACTIVE
  #include "matrix/src/platform/api/Model_OpenGL.h"
  #include "matrix/src/platform/api/Shader_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
  #include "matrix/src/platform/api/Shader_DirectX.h"
#endif

#include "matrix/src/layers/SceneGraph.h"

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
    
    MX_API void push(const std::string &object_name, const std::string &file_name);
    MX_API void pop(const std::string &name);

    MX_API void setShader(const std::string &name);

  public:
    SceneGraph m_Sg;
    std::string m_Name;
  };
}

#endif // LEVEL_H