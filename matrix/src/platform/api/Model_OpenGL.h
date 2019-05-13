#ifndef MODEL_OPENGL_H
#define MODEL_OPENGL_H

#include "matrix/src/platform/api/Model.h"

namespace MX
{
  struct GL_ModelObjects
  {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int NBO;
    unsigned int TBO;
    unsigned int EBO;

    unsigned int draw_mode;
    int num_elements;
  };

  class Model_OpenGL : public Model
  {
  public:    
    MX_API Model_OpenGL();
    MX_API Model_OpenGL(const Model_OpenGL &model);
    MX_API Model_OpenGL(const std::string &name, bool instantInitialize = 0);
    MX_API ~Model_OpenGL() {}
    
    MX_API void initialize() override;
    MX_API void draw() override;
    MX_API void setGeometry(unsigned int draw_mode) override;

    MX_API void setName(const std::string &name);

  private:
    GL_ModelObjects m_ModelObject; 
  };
}

#endif // MODEL_OPENGL_H