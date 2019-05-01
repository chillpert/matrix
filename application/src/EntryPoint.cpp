#include "matrix/Matrix.h"

MX::Level l1("level1");

void initialize() 
{
  MX_MODEL model("monkey.obj", 1);
  l1.push(model);
  l1.initialize();
}

void update()
{
  l1.update();
}

void render() 
{
  l1.render();
}

int main() 
{
  // application testing
  MX::app.m_Window->setTitle("My Application");
  MX::app.initialize(initialize);

  // rendering loop
  while(MX::app.m_Running) 
  {
    MX::app.update(update);        
    MX::app.render(render);
  }
  MX::app.clean();
  
  return 0;
}