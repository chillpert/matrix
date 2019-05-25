#ifndef SHADER_H
#define SHADER_H

#ifdef MX_OPENGL_ACTIVE
  #define MX_SHADER MX::Shader_OpenGL
#elif
  #define MX_SHADER MX::Shader_DirectX
#endif

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  class Shader
  {
  public:
    MX_API Shader()
        : m_VsPath(MX_SHADER_PATH), m_FsPath(MX_SHADER_PATH) {}
    MX_API ~Shader() {}

    MX_API void setPaths(const std::string &vsPath, const std::string &fsPath);
    MX_API void setVsPath(const std::string &vsPath);
    MX_API void setFsPath(const std::string &fsPath);
    MX_API void setName(const std::string &name);

    MX_API virtual void update() {}

    MX_API inline std::string &getName() { return m_Name; }
    MX_API inline std::string &getVsPath() { return m_VsPath; }
    MX_API inline std::string &getFsPath() { return m_FsPath; }
    MX_API inline std::string &getVsSource() { return m_VsSource; }
    MX_API inline std::string &getFsSource() { return m_FsSource; }
    
  protected:
    std::string m_Name;
    std::string m_VsPath;
    std::string m_FsPath;
    std::string m_VsSource;
    std::string m_FsSource;
  };
}

#endif // SHADER_H