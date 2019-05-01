#ifndef WORLD_H
#define WORLD_H

#include "matrix/src/layers/Level.h"

namespace MX 
{
  class World
  {
  public:
    World() {}
    ~World() {}

    void push(const Level &lv);
    void render();

    void setActiveLevel(const Level &lv);
    Level &getActiveLevel() { return activeLevel; }

  private:
    Level activeLevel;
    std::vector<Level> levels;
  };
}

#endif // WORLD_H