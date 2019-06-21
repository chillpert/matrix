#include <Texture.h>

namespace MX
{
  Texture::Texture(const std::string &name, const std::string &path)
  {
    m_Name = name;
    m_path = path + name;
  }
}