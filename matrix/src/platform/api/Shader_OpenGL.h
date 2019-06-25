#ifndef SHADER_OPENGL_H
#define SHADER_OPENGL_H

#include <Shader.h>

namespace MX
{
  class Shader_OpenGL : public Shader
  {
  public:
    MX_API Shader_OpenGL() = default;
    MX_API Shader_OpenGL(const std::string &name, bool instant_init = 0);
    MX_API ~Shader_OpenGL();

    MX_API Shader_OpenGL(const Shader_OpenGL&) = default;
    MX_API Shader_OpenGL &operator=(const Shader_OpenGL&) = default;
    
    MX_API void initialize() override;
    MX_API void update() override;
    MX_API void use() const override;

    MX_API u_int32_t getID() const override { return static_cast<u_int32_t>(m_ID); }
    MX_API u_int32_t compile(u_int32_t type, const std::string &source);
    MX_API bool errorCheck(int type) const;

    MX_API void setBool(const std::string &name, const bool &value) const override;
    MX_API void setInt(const std::string &name, const int &value) const override;
    MX_API void setFloat(const std::string &name, const float &value) const override;
    MX_API void setfVec2(const std::string &name, const glm::fvec2 &value) const override;
    MX_API void setfVec3(const std::string &name, const glm::fvec3 &value) const override;
    MX_API void setfVec4(const std::string &name, const glm::fvec4 &value) const override;
    MX_API void setfMat2(const std::string &name, const glm::fmat2 &mat) const override;
    MX_API void setfMat3(const std::string &name, const glm::fmat3 &mat) const override;
    MX_API void setfMat4(const std::string &name, const glm::fmat4 &mat) const override;

  public:
    GLuint m_ID;
  };
}

#endif // SHADER_OPENGL_H