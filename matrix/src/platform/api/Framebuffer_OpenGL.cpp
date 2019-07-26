#include <Framebuffer_OpenGL.h>
#include <Application.h>

namespace MX
{
  Framebuffer_OpenGL::Framebuffer_OpenGL(bool instant_init)
    : Framebuffer(instant_init) { }

  Framebuffer_OpenGL::~Framebuffer_OpenGL()
  {
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(1, &m_tex);
    glDeleteVertexArrays(1, &m_quad_vao);
    glDeleteVertexArrays(1, &m_quad_vbo);
  }

  bool Framebuffer_OpenGL::initialize()
  {
    m_shader.setPath("screen_buffer");
    m_shader.initialize();

    m_shader.use();
    m_shader.setInt("screen_texture", 0);

    auto viewport = Application::get().m_Window->m_Props.m_Viewport;

    glGenFramebuffers(1, &m_fbo);

    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, max_window_width, max_window_height, 0, GL_RGBA, GL_FLOAT, NULL);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glViewport(
      viewport.m_Viewport_min_x,
      viewport.m_Viewport_min_y,
      viewport.m_Viewport_max_x,
      viewport.m_Viewport_max_y
    );

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, max_window_width, max_window_height);

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
      unbind();
      MX_FATAL("MX: Framebuffer: OpenGL: Initialization");
      return false;
    }

    unbind();

    m_initialized = 1;
    m_needs_refresh = 1;
    MX_SUCCESS("MX: Framebuffer: OpenGL: Initialization");
    return true;
  }

  void Framebuffer_OpenGL::bind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  }

  void Framebuffer_OpenGL::unbind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void Framebuffer_OpenGL::render()
  {
    m_shader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    render_quad();
  }

  void Framebuffer_OpenGL::update()
  {
    upload_settings();
  }

  void Framebuffer_OpenGL::resize()
  {
    glDeleteTextures(1, &m_tex);

    auto viewport = Application::get().m_Window->m_Props.m_Viewport;

    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, viewport.m_Viewport_max_x, viewport.m_Viewport_max_y, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, viewport.m_Viewport_max_x, viewport.m_Viewport_max_y);

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex, 0);
    unbind();
  }

  void Framebuffer_OpenGL::render_quad()
  {
    if (m_quad_vao == 0)
    {
      float quad_vertices[] = {
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
      };

      glGenVertexArrays(1, &m_quad_vao);
      glGenBuffers(1, &m_quad_vbo);
      glBindVertexArray(m_quad_vao);
      glBindBuffer(GL_ARRAY_BUFFER, m_quad_vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &quad_vertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }

    glBindVertexArray(m_quad_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
  }

  void Framebuffer_OpenGL::upload_settings() const
  {
    m_shader.use();
    m_shader.setBool("inverse_color", m_settings.inverse_color);
    m_shader.setBool("depth_map", m_settings.depth_map);
    m_shader.setBool("shadow_map", m_settings.shadow_map);
  }
}