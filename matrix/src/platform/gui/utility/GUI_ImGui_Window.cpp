#include "GUI_ImGui_Window.h"
#include "Application.h"

namespace MX
{
  ImGui_Window::ImGui_Window()
    : m_p_enabled(true),
      m_p_open(true),
      m_called_begin(false),
      m_window_flags(0) { }

  bool ImGui_Window::initialize(const char* name, ImGuiWindowFlags flags)
  {
    m_name = name;
    set_flags(flags);
    return true;
  }

  bool ImGui_Window::update()
  {
    if (!m_p_enabled)
      return false;

    return m_p_enabled;
  }

  void ImGui_Window::render()
  {
    
  }

  /*
  Usage:
    1. if (ImGui_Window::begin()) { *run code* }
    2. ImGui_Window::end();
  */
  bool ImGui_Window::begin()
  {
    // don't show window if it isn't enabled
    if (!m_p_enabled)
      return false;

    activate_styles();
    m_called_begin = ImGui::Begin(m_name, &m_p_open, m_window_flags);
    remove_styles();

    if (m_called_begin)
      resize_on_max_size();

    return m_called_begin; 
  }

  void ImGui_Window::end()
  {  
    if (!m_p_enabled)
      return;

    ImGui::End();
  }

  void ImGui_Window::add_flags(ImGuiWindowFlags flags)
  {
    m_window_flags |= flags;
  }

  void ImGui_Window::set_flags(ImGuiWindowFlags flags)
  {
    m_window_flags = 0;
    m_window_flags = flags;
  }

  void ImGui_Window::push_style(ImGuiStyleVar idx, const ImVec2& val)
  {
    m_style_vector.push_back({idx, val});
  }

  void ImGui_Window::push_style(ImGuiStyleVar idx, float val)
  {
    m_style_float.push_back({idx, val});
  }

  void ImGui_Window::activate_styles()
  {
    size_t amount = m_style_vector.size() + m_style_float.size();
    if (amount > 0)
    {
      for (auto it : m_style_vector)
        ImGui::PushStyleVar(it.first, it.second);

      for (auto it : m_style_float)
        ImGui::PushStyleVar(it.first, it.second);
    }
  }

  void ImGui_Window::remove_styles()
  {
    size_t amount = m_style_vector.size() + m_style_float.size();
    if (amount > 0)
      ImGui::PopStyleVar();
  }

  void ImGui_Window::resize_on_max_size()
  {
    auto x_win_size = ImGui::GetWindowSize().x;
    auto y_win_size = ImGui::GetWindowSize().y;

    auto x_win_pos = ImGui::GetWindowPos().x;
    auto y_win_pos = ImGui::GetWindowPos().y;

    auto screen_x = MX_WINDOW->m_Props.m_Width;
    auto screen_y = MX_WINDOW->m_Props.m_Height;

    auto x_win_pos_fix = screen_x - x_win_pos;
    auto y_win_pos_fix = screen_y - y_win_pos;

    if (x_win_size > x_win_pos_fix)
      ImGui::SetWindowSize(ImVec2(x_win_pos_fix, y_win_size));

    if (y_win_size > y_win_pos_fix)
      ImGui::SetWindowSize(ImVec2(x_win_size, y_win_pos_fix));
  }

  void resize_on_max_size()
  {
    auto x_win_size = ImGui::GetWindowSize().x;
    auto y_win_size = ImGui::GetWindowSize().y;

    auto x_win_pos = ImGui::GetWindowPos().x;
    auto y_win_pos = ImGui::GetWindowPos().y;

    auto screen_x = MX_WINDOW->m_Props.m_Width;
    auto screen_y = MX_WINDOW->m_Props.m_Height;

    auto x_win_pos_fix = screen_x - x_win_pos;
    auto y_win_pos_fix = screen_y - y_win_pos;

    if (x_win_size > x_win_pos_fix)
      ImGui::SetWindowSize(ImVec2(x_win_pos_fix, y_win_size));

    if (y_win_size > y_win_pos_fix)
      ImGui::SetWindowSize(ImVec2(x_win_size, y_win_pos_fix));
  }
}