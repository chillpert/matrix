#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdafx.h>
#include <Model.h>
#include <Shader.h>

namespace MX
{
  class Framebuffer
  {
  public:
    MX_API Framebuffer(bool instant_init);
    MX_API virtual ~Framebuffer() = default;

    Framebuffer(const Framebuffer&) = default;
    Framebuffer &operator=(const Framebuffer&) = default; 

  protected:
    MX_API virtual bool initialize();
    MX_API virtual void update() = 0;
    MX_API virtual void render() = 0;

  public:
    std::shared_ptr<Model> m_quad;
    std::shared_ptr<Shader> m_screen_shader;

    bool m_initialized;
  };

}

#endif // FRAMEBUFFER_H