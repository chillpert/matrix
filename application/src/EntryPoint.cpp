#define GLM_ENABLE_EXPERIMENTAL 
#include <GLM/gtx/string_cast.hpp>

#include "matrix/Matrix.h"

/* 
  order to draw stuff
   1. initialize shader
   2. create shader
   3. initialize model
   4. parse model
   5. activate shader
   6. upload all three matrices
   7. bind vertex arrays
   8. draw
   9. bind default
*/  

MX_MODEL m1("monkey.obj");
MX_SHADER s1("trivial");
MX::Camera *cam = &MX::Camera::get();

void initialize() 
{
  s1.create();
  m1.initialize(); 
}

void update() 
{  
  s1.use();
  glm::fmat4 view_matrix = cam->getViewMatrix();
  glm::fmat4 projection_matrix = cam->getProjectionMatrix();
  s1.setfMat4("view", view_matrix);
  s1.setfMat4("projection", projection_matrix);
}

float time_ = 0.0f;

void render() 
{
  time_ = float(SDL_GetTicks()) / 1000.0f;

  s1.use();
  glm::fmat4 model_matrix = glm::fmat4(1.0f);
  model_matrix = glm::rotate(model_matrix, 2.0f * float(time_), glm::fvec3(0.0f, 1.0f, 0.0f));
  s1.setfMat4("model", model_matrix);
  s1.setfVec3("lightPosition", glm::vec3(5, -5, 1));
  s1.setfVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
  s1.setfVec3("viewPos", cam->m_Position);

  m1.draw();
}

int main() 
{
  // application testing
  MX::Application* app = &MX::Application::get();

  app->getWindow()->setTitle("My Application");
  app->initialize(initialize);

  // rendering loop
  while(app->isRunning()) 
  {
    app->update(update);        
    app->render(render);
  }
  app->clean();
  
  return 0;
}