#ifndef WORLD_H
#define WORLD_H

/*
disabled for faster start up

  #define MX_INSTANT_TEXTURE_INIT
  #define MX_INSTANT_MODEL_INIT
*/

#define MX_INSTANT_SHADER_INIT
#define MX_INSTANT_SCENE_INIT

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/layers/Scene.h"

#include "matrix/src/platform/api/Shader.h"
#include "matrix/src/platform/api/Model.h"
#include "matrix/src/platform/api/Texture.h"
#ifdef MX_OPENGL_ACTIVE
  #include "matrix/src/platform/api/Model_OpenGL.h"
  #include "matrix/src/platform/api/Shader_OpenGL.h"
  #include "matrix/src/platform/api/Texture_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
  #include "matrix/src/platform/api/Shader_DirectX.h"
  #include "matrix/src/platform/api/Texture_DirectX.h"
#endif

namespace MX 
{
  class World
  {
  public:
    MX_API static World &get();
    MX_API ~World();

    MX_API void initialize();
    MX_API void update();
    MX_API void render();

    MX_API void push(Scene *scene);
    MX_API void pop(const std::string &name);
  
  private:
    MX_API World() {}

  public:
    Scene *m_ActiveScene;
    std::vector<Scene*> m_ExistingScenes;
  
    std::vector<MX_MODEL*> m_Models;
    std::vector<MX_SHADER*> m_Shaders;
    std::vector<MX_TEXTURE*> m_Textures;
  };
}

#endif // WORLD_H