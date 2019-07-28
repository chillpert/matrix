#ifndef FRAMEBUFFER_OPENGL_H
#define FRAMEBUFFER_OPENGL_H

#include <Framebuffer.h>

namespace MX
{
  class Framebuffer_OpenGL : public Framebuffer
  {
  public:
    MX_API Framebuffer_OpenGL(bool instant_init = 0);
    MX_API virtual ~Framebuffer_OpenGL();

    MX_API Framebuffer_OpenGL(const Framebuffer_OpenGL&) = default;
    MX_API Framebuffer_OpenGL &operator=(const Framebuffer_OpenGL&) = default;

    MX_API bool initialize() override;
    MX_API void bind() override;
    MX_API void unbind() override;
    MX_API void render() override;
    MX_API void update() override;
    MX_API void refresh() override;
    MX_API void upload_settings() const override;

  private:
    MX_API void render_quad() override;

  public:
    bool m_off_screen = false;

    GLuint m_fbo;
    GLuint m_rbo;
    GLuint m_tex;
    GLuint m_depth_tex;
    GLuint m_quad_vbo;
    GLuint m_quad_vao;
  };
}

#endif // FRAMEBUFFER_OPENGL_H