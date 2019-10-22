#include "Editor_Viewport.h"
#include "Application.h"

namespace MX
{
  Editor_Viewport::Editor_Viewport()
  {
    
  }

  void Editor_Viewport::initialize()
  {
    
  }

  void Editor_Viewport::render()
  {
    ImGui::Begin("EditorViewport", &p_open, window_flags);

    auto window_size = ImGui::GetWindowSize();
    auto window_pos = ImGui::GetWindowPos();
    
    static bool is_black = false;
    static bool flag = false;
    static bool first_iteration = true;
    
    // check for window resizing
    static ImVec2 prev_window_size;
    if (window_size.x != prev_window_size.x || window_size.y != prev_window_size.y)
    {
      Application::get().m_API->m_framebuffer.m_needs_refresh = 1;

      if (first_iteration)
      {
        first_iteration = false;
      }
      else
      {
        flag = true;
        is_black = true;
      }
    }

    if (flag)
    {
      if (!ImGui::IsMouseReleased(0))
      {
        is_black = true;
      }
      else
      {
        is_black = false;
        flag = false;
      }
    }

    prev_window_size = window_size;

    // update viewport for api
    Window::WindowProps::ViewPort* app_viewport = &Application::get().m_Window->m_Props.m_Viewport;

    app_viewport->m_Viewport_min_x = window_pos.x;
    app_viewport->m_Viewport_min_y = Application::get().m_Window->m_Props.m_Height - (window_size.y + window_pos.y);

    app_viewport->m_Viewport_max_x = window_size.x;
    app_viewport->m_Viewport_max_y = window_size.y;

    auto window_size_avail = ImGui::GetContentRegionAvail();

    // refresh when viewport gets docked or undocked
    bool docked = ImGui::IsWindowDocked();
    static bool prev_docked = false;

    if (docked != prev_docked)
    {
      Application::get().m_API->m_framebuffer.m_needs_refresh = 1;
      is_black = false;
      flag = false;
    }

    prev_docked = docked;

    // draw render preview while window size doesn't change
    if (!is_black)
    {
      m_id = (void*) Application::get().m_API->m_framebuffer.m_tex;
      ImGui::Image(m_id, ImVec2(window_size_avail.x, window_size_avail.y), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
    }

    ImGui::End();
  }
}