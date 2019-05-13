#include "matrix/Matrix.h"

MX::Level debug_level("level1");

void initialize() 
{
  MX::World::get().m_ActiveLevel = &debug_level;
  debug_level.initialize();
}

void update()
{
  debug_level.update();
}

void render() 
{
  debug_level.render();
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