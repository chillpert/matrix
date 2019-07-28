#include <Framebuffer_OpenGL.h>
#include <Application.h>

namespace MX
{
  float near_plane = 1.0f;
  float far_plane = 7.5f;

  Framebuffer_OpenGL::Framebuffer_OpenGL(bool instant_init)
  {
    if (instant_init)
      if (initialize())
        m_initialized = 1;
  }

  Framebuffer_OpenGL::~Framebuffer_OpenGL()
  {
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(1, &m_tex);
    glDeleteTextures(1, &m_depth_tex);
    glDeleteVertexArrays(1, &m_quad_vao);
    glDeleteVertexArrays(1, &m_quad_vbo);
  }

  bool Framebuffer_OpenGL::initialize()
  {
    m_quad_shader = MX_GET_SHADER("screen_buffer");
    m_depth_shader = MX_GET_SHADER("simple_depth");

    m_quad_shader->use();
    m_quad_shader->setInt("screen_texture", 0);
    m_quad_shader->setInt("depth_texture", 1);

    auto viewport = Application::get().m_Window->m_Props.m_Viewport;

    glGenFramebuffers(1, &m_fbo);

    if (m_depth_map)
    {
      // depth map texture
      glGenTextures(1, &m_depth_tex);
      glBindTexture(GL_TEXTURE_2D, m_depth_tex);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, max_window_width, max_window_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
    else
    {
      // default texture
      glGenTextures(1, &m_tex);
      glBindTexture(GL_TEXTURE_2D, m_tex);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, max_window_width, max_window_height, 0, GL_RGBA, GL_FLOAT, NULL);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glViewport(
      viewport.m_Viewport_min_x,
      viewport.m_Viewport_min_y,
      viewport.m_Viewport_max_x,
      viewport.m_Viewport_max_y
    );

    if (m_depth_map)
    {
      bind();
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_tex, 0);
    }
    else
    {
      // default initialization
      glGenRenderbuffers(1, &m_rbo);
      glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, max_window_width, max_window_height);

      bind();

      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex, 0);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    }

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
    m_quad_shader->use();

    m_quad_shader->setFloat("near_plane", near_plane);
    m_quad_shader->setFloat("far_plane", far_plane);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, m_depth_tex);

    render_quad();

    //shadows
    auto shader = MX_GET_SHADER("blinn_phong");
    shader->setInt("shadowMap", 0);
    shader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_depth_tex);
  }

  void Framebuffer_OpenGL::update()
  {
    static bool prev_depth_map = m_depth_map;

    if (prev_depth_map != m_depth_map)
      refresh();

    upload_settings();
  }

  void Framebuffer_OpenGL::refresh()
  {
    auto viewport = Application::get().m_Window->m_Props.m_Viewport;

    if (m_depth_map)
    {
      glDeleteTextures(1, &m_depth_tex);

      // depth map texture
      glGenTextures(1, &m_depth_tex);
      glBindTexture(GL_TEXTURE_2D, m_depth_tex);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, viewport.m_Viewport_max_x, viewport.m_Viewport_max_y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

      bind();
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_tex, 0);
    }
    else
    {
      glDeleteTextures(1, &m_tex);

      // default texture
      glGenTextures(1, &m_tex);
      glBindTexture(GL_TEXTURE_2D, m_tex);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, viewport.m_Viewport_max_x, viewport.m_Viewport_max_y, 0, GL_RGBA, GL_FLOAT, NULL);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glGenRenderbuffers(1, &m_rbo);
      glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, viewport.m_Viewport_max_x, viewport.m_Viewport_max_y);

      bind();
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex, 0);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    }

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
    glm::vec3 light_pos(-2.0f, 4.0f, -1.0f);

    glm::mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 light_view = glm::lookAt(light_pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 light_space_matrix = light_projection * light_view;

    auto shader = MX_GET_SHADER("blinn_phong");
    shader->use();
    shader->setfMat4("lightSpaceMatrix", light_space_matrix);

    m_depth_shader->use();
    m_depth_shader->setfMat4("light_space_matrix", light_space_matrix);

    m_quad_shader->use();
    m_quad_shader->setBool("depth_map", m_depth_map);

    m_quad_shader->use();
    m_quad_shader->setBool("inverse_color", m_inversed_color);
  }
}