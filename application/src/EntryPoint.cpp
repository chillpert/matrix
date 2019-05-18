#include "matrix/Matrix.h"

MX::Scene debug_scene("The Void");
MX::Scene debug_scene2("Main Menu");

void initialize()
{
  // MX::World::get().m_ActiveScene = &debug_scene;
  MX::World::get().push(&debug_scene2);
  MX::World::get().push(&debug_scene);

  MX::World::get().initialize();
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