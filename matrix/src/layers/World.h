#ifndef WORLD_H
#define WORLD_H

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/layers/Scene.h"

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
  };
}

#endif // WORLD_H