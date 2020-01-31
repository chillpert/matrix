#include "Matrix.h"

void initialize()
{
  using namespace MX;
  MX_WORLD.initialize();
  
  //MX_WORLD.push(std::make_shared<Scene>("My First Scene"));
}

void update()
{
  using namespace MX;
  MX_WORLD.update();
}

void render()
{
  using namespace MX;
  MX_WORLD.render();
}

int main()
{
  // application testing
  MX::Application::get().initialize(initialize);

  // rendering loop
  while (MX::Application::get().m_Running)
  {
    MX::Application::get().update(update);
    MX::Application::get().render(render);
  }
  MX::Application::get().clean();
  
  return 0;
}