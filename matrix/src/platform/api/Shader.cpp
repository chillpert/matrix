#include <Shader.h>

namespace MX {

  Shader::Shader(const std::string &name)
  {
    setPath(name);
  }

  void Shader::setPath(const std::string &name)
  {
    m_Name = name;
    m_VsPath.append(name + ".vert");
    m_FsPath.append(name + ".frag");
  }

  void use(Shader &shader)
  {
   shader.use();
  }
}