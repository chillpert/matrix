#include "matrix/Matrix.h"

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

void render() 
{
  s1.use();
  glm::fmat4 model_matrix = glm::fmat4(1.0f);
  model_matrix = glm::rotate(model_matrix, 2.0f * float(MX::app.m_Window->m_Props.m_Time), glm::fvec3(0.0f, 1.0f, 0.0f));
  s1.setfMat4("model", model_matrix);
  s1.setfVec3("lightPosition", glm::vec3(5, -5, 1));
  s1.setfVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
  s1.setfVec3("viewPos", cam->getPosition());

  m1.draw();
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