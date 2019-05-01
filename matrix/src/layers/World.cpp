#include "matrix/src/layers/World.h"

namespace MX
{
  void World::push(const Level &level)
  {
    levels.push_back(level);
  }

  void World::render()
  {
    activeLevel.render();
  }

  void World::setActiveLevel(const Level &lv)
  {
    activeLevel = lv;
  }
}