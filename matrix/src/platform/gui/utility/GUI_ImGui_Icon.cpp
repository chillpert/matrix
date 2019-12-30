#include "GUI_ImGui_Icon.h"
#include "Application.h"

namespace MX
{
  ImGui_Icon::ImGui_Icon(const std::string& name, float size_x, float size_y) :
    m_uv0(ImVec2(0, 0)),
    m_uv1(ImVec2(1, 1)),
    m_tint_col(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)),
    m_border_col(ImVec4(1.0f, 1.0f, 1.0f, 0.0f)),
    m_path(MX_MATRIX_ICONS + name),
    m_size_x(size_x),
    m_size_y(size_y),
    m_texture(std::make_unique<MX_TEXTURE>(m_path))
  {
    initialize();
  }

  void ImGui_Icon::initialize()
  {
    m_texture->initialize();

    // cast to opengl texture (requires changes as soon as renderer supports other APIs)
    m_derived_tex_ptr = static_cast<MX_TEXTURE*>(m_texture.get());

    m_tex_id = (void*)m_derived_tex_ptr->getID();

    if (m_size_x == -1.0f && m_size_y == -1.0f)
    {
      auto window_pos = ImGui::GetWindowPos();
      auto application_window_size = ImVec2(
        static_cast<float>(Application::get().m_Window->m_Props.m_Width),
        static_cast<float>(Application::get().m_Window->m_Props.m_Height)
      );

      auto max_size = ImVec2(
        application_window_size.x - window_pos.x,
        application_window_size.y - window_pos.y
      );

      if (m_derived_tex_ptr->m_Stb.width > max_size.x)
        m_size_x = max_size.x;
      else
        m_size_x = static_cast<float>(m_derived_tex_ptr->m_Stb.width);

      if (m_derived_tex_ptr->m_Stb.height > max_size.y)
        m_size_y = max_size.y;
      else
        m_size_y = static_cast<float>(m_derived_tex_ptr->m_Stb.height);
    }
  }

  void ImGui_Icon::render()
  {
    ImGui::Image(m_tex_id, ImVec2(m_size_x, m_size_y), m_uv0, m_uv1, m_tint_col, m_border_col);
  }

  bool ImGui_Icon::render_as_button(int frame_padding, const ImVec4& bg_col)
  {
    return ImGui::ImageButton(m_tex_id, ImVec2(m_size_x, m_size_y), m_uv0, m_uv1, frame_padding, bg_col, m_tint_col);
  }

  void ImGui_Icon::set_corners(const ImVec2& uv0, const ImVec2& uv1)
  {
    m_uv0 = uv0;
    m_uv1 = uv1;
  }

  void ImGui_Icon::set_tint_color(const ImVec4& tint_color)
  {
    m_tint_col = tint_color;
  }

  void ImGui_Icon::set_border_color(const ImVec4& border_color)
  {
    m_border_col = border_color;
  }
}