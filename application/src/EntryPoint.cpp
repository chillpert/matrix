#include "matrix/Matrix.h"

void initialize()
{
  MX::World::get().push(new MX::Scene("debug"));

  MX::World::get().initialize();

#ifndef MX_IMGUI_ACTIVE
  MX::World::get().m_ActiveScene->push("debug node", "sphere.obj", "root");
#endif
}

void update()
{
  MX::World::get().update();
}

void render()
{
  MX::World::get().render();
}

int main()
{
  // application testing
  MX::Application::get().initialize(initialize);
  MX::Application::get().m_Window->setTitle("My Application");

  // rendering loop
  while(MX::Application::get().m_Running)
  {
    MX::Application::get().update(update);
    MX::Application::get().render(render);
  }
  MX::Application::get().clean();
  
  return 0;
}