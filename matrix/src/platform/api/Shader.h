#ifndef SHADER_H
#define SHADER_H

#ifdef MX_OPENGL_ACTIVE
  #define MX_SHADER MX::Shader_OpenGL
#elif
  #define MX_SHADER MX::Shader_DirectX
#endif

#include <stdafx.h>

namespace MX
{
  class Shader
  {
  public:
    MX_API Shader() = default;
    MX_API Shader(const std::string &name);
    MX_API virtual ~Shader() = default;

    MX_API Shader(const Shader&) = default;
    MX_API Shader &operator=(const Shader&) = default;

    MX_API virtual void initialize() = 0;
    MX_API virtual void update() = 0;
    MX_API virtual void use() const = 0;

    MX_API virtual u_int32_t getID() const = 0;
    MX_API virtual u_int32_t compile(u_int32_t type, const std::string &source) = 0;
    MX_API virtual bool errorCheck(int type) const = 0;

    MX_API virtual void setBool(const std::string &name, const bool &value) const = 0;
    MX_API virtual void setInt(const std::string &name, const int &value) const = 0;
    MX_API virtual void setFloat(const std::string &name, const float &value) const = 0;
    MX_API virtual void setfVec2(const std::string &name, const glm::fvec2 &value) const = 0;
    MX_API virtual void setfVec3(const std::string &name, const glm::fvec3 &value) const = 0;
    MX_API virtual void setfVec4(const std::string &name, const glm::fvec4 &value) const = 0;
    MX_API virtual void setfMat2(const std::string &name, const glm::fmat2 &mat) const = 0;
    MX_API virtual void setfMat3(const std::string &name, const glm::fmat3 &mat) const = 0;
    MX_API virtual void setfMat4(const std::string &name, const glm::fmat4 &mat) const = 0;

    MX_API void setPath(const std::string &name);
    MX_API std::string getName() { return m_Name; }

    std::string m_Name;
    std::string m_VsPath = MX_SHADER_PATH;
    std::string m_FsPath = MX_SHADER_PATH;
    std::string m_VsSource;
    std::string m_FsSource;
    std::string m_Profile;

    bool m_initialized = 0;
  };

  MX_API void use(Shader &shader);
}

#endif // SHADER_H