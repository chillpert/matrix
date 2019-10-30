#include "GUI_ImGui_Window.h"
#include "Application.h"

namespace MX
{
  ImGui_Window::ImGui_Window()
    : m_window_flags(0),
      m_p_enabled(true),
      m_p_open(true) { }

  bool ImGui_Window::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    m_name = name;
    set_flags(flags);
    return true;
  }

  void ImGui_Window::update()
  {
    if (begin())
    {
      resize_on_max_size();
    }
    end();
  }

  bool ImGui_Window::begin()
  {
    activate_styles();
    bool flag = ImGui::Begin(m_name.c_str(), &m_p_open, m_window_flags);
    remove_styles();

    return flag;
  }

  void ImGui_Window::end()
  {
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
    int amount = m_style_vector.size() + m_style_float.size();
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
    int amount = m_style_vector.size() + m_style_float.size();
    if (amount > 0)
      ImGui::PopStyleVar();
  }

  void ImGui_Window::resize_on_max_size()
  {
    auto x_win_size = ImGui::GetWindowSize().x;
    auto y_win_size = ImGui::GetWindowSize().y;

    auto x_win_pos = ImGui::GetWindowPos().x;
    auto y_win_pos = ImGui::GetWindowPos().y;

    auto screen_x = Application::get().m_Window->m_Props.m_Width;
    auto screen_y = Application::get().m_Window->m_Props.m_Height;

    auto x_win_pos_fix = screen_x - x_win_pos;
    auto y_win_pos_fix = screen_y - y_win_pos;

    if (x_win_size > x_win_pos_fix)
      ImGui::SetWindowSize(ImVec2(x_win_pos_fix, y_win_size));

    if (y_win_size > y_win_pos_fix)
      ImGui::SetWindowSize(ImVec2(x_win_size, y_win_pos_fix));
  }
}