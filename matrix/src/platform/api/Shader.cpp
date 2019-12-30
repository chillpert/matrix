#include "Shader.h"

namespace MX {

  Shader::Shader(const std::string &path)
  {
    m_Name = path.substr(path.find_last_of("/") + 1);
    m_path = path;

    m_VsPath = path + ".vert";
    m_FsPath = path + ".frag";
  }

  void use(Shader &shader)
  {
   shader.use();
  }
}