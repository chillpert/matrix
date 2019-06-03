#ifndef TEXTURE_DIRECTX_H
#define TEXTURE_DIRECTX_H

#include "matrix/src/platform/api/Texture.h"

namespace MX
{
  class Texture_DirectX : public Texture
  {
    public:
      MX_API Texture_DirectX();
      MX_API ~Texture_DirectX();

      MX_API void initialize() override;

    private:
  };
}

#endif // TEXTURE_DIRECTX_H