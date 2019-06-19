#ifndef MODEL_OPENGL_H
#define MODEL_OPENGL_H

#include <Model.h>

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
    MX_API Model_OpenGL(const std::string &name, bool instant_init = 0);
    MX_API ~Model_OpenGL() = default;

    MX_API Model_OpenGL(const Model_OpenGL&) = default;
    MX_API Model_OpenGL &operator=(const Model_OpenGL&) = default;
    
    MX_API void initialize() override;
    MX_API void draw() override;
    MX_API void setGeometry(u_int64_t draw_mode) override;

  private:
    GL_ModelObjects m_ModelObject; 
  };
}

#endif // MODEL_OPENGL_H