#include "matrix/Matrix.h"

//MX::Camera* cam = &MX::Camera::get();
MX_MODEL model("monkey.obj");

//MX_SHADER s1("trivial");

//MX::Model_Test model("monkey.obj");
MX::Shader_Test s2("trivial");

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

void initialize() 
{
  MX::Camera_Test::get();
  //s1.create();
  //model.parse(); 
  model.setGeometry(GL_TRIANGLES);

  s2.createShader();
  //model.setGeometry(GL_TRIANGLES);
}

void update() 
{
  //s1.use();
  //glm::fmat4 view_matrix = cam->getViewMatrix();
  //glm::fmat4 projection_matrix = cam->getProjectionMatrix();
  //s1.setfMat4("view", view_matrix);
  //s1.setfMat4("projection", projection_matrix);

  s2.use();
  glm::fmat4 view_matrix = MX::Camera_Test::get().getViewMatrix();
  glm::fmat4 projection_matrix = MX::Camera_Test::get().getProjectionMatrix();
  s2.setView(view_matrix);
  s2.setProjection(projection_matrix);
}

#include <GLM/glm.hpp>
#include <SDL2/SDL.h>

float time_ = 0.0f;

void render() 
{
  s2.use();
  glm::fmat4 model_matrix = glm::fmat4(1.0f);
  //s1.setfMat4("model", model_matrix);

  time_ = float(SDL_GetTicks()) / 1000.0f;
  model_matrix = glm::rotate(model_matrix, 2.0f * time_, glm::fvec3(0.0f, 1.0f, 0.0f));
  s2.setModel(model_matrix);
  
  
  model.draw();
  //model.setVertexAttributes();
  //model.draw();
}

int main() 
{
  // application testing
  MX::Application* app = &MX::Application::get();

  app->initialize(initialize);
  app->getWindow()->setTitle("My Application");

  // rendering loop
  while(app->isRunning()) {
    app->update(update);        
    app->render(render);
  }
  app->clean();
  
  return 0;
}