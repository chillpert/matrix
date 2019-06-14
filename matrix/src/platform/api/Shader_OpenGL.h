#ifndef SHADER_OPENGL_H
#define SHADER_OPENGL_H

#include "matrix/src/platform/api/Shader.h"

namespace MX
{
  class Shader_OpenGL : public Shader
  {
  public:
    MX_API Shader_OpenGL() {}
    MX_API Shader_OpenGL(const Shader_OpenGL &shader);
    MX_API Shader_OpenGL(const std::string &name, bool instantInitialization = 0);
    MX_API virtual ~Shader_OpenGL() {}

    MX_API void initialize();
    MX_API void update() override;
    MX_API void use() const;

    MX_API void  setBool(const std::string &name, const bool &value)        const;
    MX_API void   setInt(const std::string &name, const int &value)         const;
    MX_API void setFloat(const std::string &name, const float &value)       const;
    MX_API void setfVec2(const std::string &name, const glm::fvec2 &value)  const;
    MX_API void setfVec3(const std::string &name, const glm::fvec3 &value)  const;
    MX_API void setfVec4(const std::string &name, const glm::fvec4 &value)  const;
    MX_API void setfMat2(const std::string &name, const glm::fmat2 &mat)    const;
    MX_API void setfMat3(const std::string &name, const glm::fmat3 &mat)    const;
    MX_API void setfMat4(const std::string &name, const glm::fmat4 &mat)    const;

    MX_API GLuint &getID() { return m_ID; }
  private:
    GLuint m_ID;
  };

  MX_API void use(Shader_OpenGL &shader);
  MX_API GLuint compile(GLuint type, const std::string& source);

  // prints and logs error message if available
  MX_API bool errorCheck(const GLuint &ID, GLint type);
}

#endif // SHADER_OPENGL_H