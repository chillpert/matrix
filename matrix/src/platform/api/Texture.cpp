#include "Texture.h"

namespace MX
{
  Texture::Texture(const std::string& path)
  {
    m_Name = path.substr(path.find_last_of("/") + 1);
    m_path = path;
  }
}