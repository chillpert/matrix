#include "matrix/src/platform/api/Shader.h"

namespace MX {

  void Shader::setPaths(const std::string &vsPath, const std::string &fsPath)
  {
    m_VsPath = vsPath;
    m_FsPath = fsPath;
  }

  void Shader::setVsPath(const std::string &vsPath)
  {
    m_VsPath = vsPath;
  }

  void Shader::setFsPath(const std::string &fsPath)
  {
    m_FsPath = fsPath;
  }

  void Shader::setName(const std::string &name)
  {
    m_Name = name;
    m_VsPath.append(name + ".vert");
    m_FsPath.append(name + ".frag");
  }
}