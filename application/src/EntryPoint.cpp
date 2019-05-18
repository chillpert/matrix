#include "matrix/Matrix.h"

MX::Scene debug_scene("scene1");

void initialize()
{
  MX::World::get().m_ActiveScene = &debug_scene;
  debug_scene.initialize();
}

void update()
{
  debug_scene.update();
}

void render()
{
  debug_scene.render();
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