#include "GUI_ImGui_Window.h"
#include "Application.h"

namespace MX
{
  bool ImGui_Window::initialize(char* name, ImGuiWindowFlags flags)
  {
    m_name = name;
    m_window_flags |= flags;
    return true;
  }

  void ImGui_Window::update()
  {
    ImGui::Begin(m_name);

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

    ImGui::End();
  }

  void ImGui_Window::begin()
  {
    ImGui::Begin(m_name, &p_open, m_window_flags);
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
}