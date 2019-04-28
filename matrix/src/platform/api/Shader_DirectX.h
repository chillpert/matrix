#ifndef SHADER_DIRECT_X
#define SHADER_DIRECT_X

#include "matrix/src/platform/api/Shader.h"

namespace MX
{
  class Shader_DirectX : public Shader
  {
  public:
    MX_API Shader_DirectX() {}
    MX_API Shader_DirectX(const std::string &name);
    MX_API ~Shader_DirectX() {}

    MX_API inline unsigned int &getID() { return m_ID; }
  private:
    unsigned int m_ID;
  };
}

#endif // SHADER_DIRECT_X