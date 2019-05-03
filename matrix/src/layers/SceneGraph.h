#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include "matrix/src/pch/stdafx.h"

#include "matrix/src/platform/api/Model.h"
#include "matrix/src/platform/api/Shader.h"
#ifdef MX_OPENGL_ACTIVE
  #include "matrix/src/platform/api/Model_OpenGL.h"
  #include "matrix/src/platform/api/Shader_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
  #include "matrix/src/platform/api/Shader_DirectX.h"
#endif

#include "matrix/src/layers/Node.h"

namespace MX 
{
  class SceneGraph
  {
  public:
    MX_API SceneGraph() {}
    MX_API ~SceneGraph() {}

    MX_API void initialize();
    MX_API void update();
    MX_API void render();
    
  private:
    MX_API void recursive_render(Node &it, glm::fmat4 &mat = glm::fmat4(1.0f));

  public:
    Node *m_Root = new Node("root of sg");
    std::vector<MX_MODEL> m_Models;
    MX_SHADER m_Shader; 
  };
}

#endif // SCENEGRAPH_HPP