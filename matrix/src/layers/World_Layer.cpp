#include "World_Layer.h"
#include "Application.h"

namespace MX
{
  World_Layer::World_Layer(const std::string& name)
    : Layer(name) { }

  void World_Layer::onAttach()
  {
    MX_WORLD.initialize();
  }

  void World_Layer::onDetach() { }

  void World_Layer::onUpdate()
  {
    MX_WORLD.update();
  }

  void World_Layer::onRender()
  {
    MX_WORLD.render();
  }

  void World_Layer::onEvent(Event& event) { }
}