#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdafx.h>
#include <Model.h>
#include <Shader.h>

#ifdef MX_PLATFORM_WINDOWS_X64
  #define MX_FRAMEBUFFER Framebuffer_OpenGL
#elif MX_PLATFORM_UNIX_X64
  #define MX_FRAMEBUFFER Framebuffer_OpenGL
#endif


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
    MX_API virtual void bind() = 0;
    MX_API virtual void unbind() = 0;
    MX_API virtual void render() = 0;
    MX_API virtual void update() = 0;
    MX_API virtual void resize() = 0;
    MX_API virtual void render_quad() = 0;
    MX_API virtual void upload_settings() const = 0;

  private:
    struct Framebuffer_Settings
    {
      bool inverse_color = 1;
      bool depth_map = 0;
      bool shadow_map = 0;
    };

  public:
    std::shared_ptr<Model> m_quad;
    std::shared_ptr<Shader> m_screen_shader;

    bool m_initialized = 0;
    bool m_needs_refresh = 1;
    bool m_is_active = 1;

    Framebuffer_Settings m_settings;
  };

}

#endif // FRAMEBUFFER_H