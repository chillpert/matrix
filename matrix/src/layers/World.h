#ifndef WORLD_H
#define WORLD_H

#include "matrix/src/pch/stdafx.h"
#include "matrix/src/layers/Level.h"

namespace MX 
{
  class World
  {
  public:
    MX_API static World &get();
    MX_API ~World() {}

    MX_API void initialize();
    MX_API void update();
    MX_API void render();

    MX_API void push(Level *level);
    MX_API void pop(const std::string &name);
  
  private:
    MX_API World() {}

  public:
    Level *m_ActiveLevel;
    std::vector<Level*> m_ExistingLevels;
  };
}

#endif // WORLD_H