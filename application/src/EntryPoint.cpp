#include "Matrix.h"

using namespace MX;

void initialize()
{
  MX_WORLD.initialize();
  
  //MX_WORLD.push(std::make_shared<Scene>("My First Scene"));
}

void update()
{
  MX_WORLD.update();
}

void render()
{
  MX_WORLD.render();
}

int main()
{
  // application testing
  MX_APP.initialize(initialize);

  // rendering loop
  while (MX_APP.m_Running)
  {
    MX_APP.update(update);
    MX_APP.render(render);
  }
  MX_APP.clean();
  
  return 0;
}