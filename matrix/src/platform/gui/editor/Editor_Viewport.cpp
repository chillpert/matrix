#include "Editor_Viewport.h"
#include "Application.h"

namespace MX
{
  Editor_Viewport::Editor_Viewport(const std::string& name, ImGuiWindowFlags flags)
  {
    initialize(name, flags);
  }

  bool Editor_Viewport::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Viewport::update()
  {
    return ImGui_Window::update();
  }
  
  void Editor_Viewport::render()
  {
    if (ImGui_Window::begin())
    {
      auto window_size = ImGui::GetWindowSize();
      auto window_pos = ImGui::GetWindowPos();

      static bool is_black = false;
      static bool flag = false;
      static bool first_iteration = true;

      static bool aspect_free = true;
      static bool aspect_4_3 = false;
      static bool aspect_16_9 = false;
      static bool aspect_21_9 = false;

      if (ImGui::BeginMenuBar())
      {
        if (ImGui::BeginMenu("Aspect"))
        {
          if (ImGui::MenuItem("Fit",  NULL, &aspect_free, !aspect_free)) 
          {
            aspect_free = true; aspect_4_3 = false; aspect_16_9 = false; aspect_21_9 = false;
            MX_GAPI->m_framebuffer.m_needs_refresh = 1;
          }
          if (ImGui::MenuItem("4:3",  NULL, &aspect_4_3,  !aspect_4_3 ))
          {
            aspect_free = false; aspect_4_3 = true; aspect_16_9 = false; aspect_21_9 = false;
            MX_GAPI->m_framebuffer.m_needs_refresh = 1;
          }
          if (ImGui::MenuItem("16:9", NULL, &aspect_16_9, !aspect_16_9))
          {
            aspect_free = false; aspect_4_3 = false; aspect_16_9 = true; aspect_21_9 = false;
            MX_GAPI->m_framebuffer.m_needs_refresh = 1;
          }
          if (ImGui::MenuItem("21:9", NULL, &aspect_21_9, !aspect_21_9))
          {
            aspect_free = false; aspect_4_3 = false; aspect_16_9 = false; aspect_21_9 = true;
            MX_GAPI->m_framebuffer.m_needs_refresh = 1;
          }

          ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
      }

      // check for window resizing
      static ImVec2 prev_window_size;
      if (window_size.x != prev_window_size.x || window_size.y != prev_window_size.y)
      {
        MX_GAPI->m_framebuffer.m_needs_refresh = 1;

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
        // makes content of viewport appear on screen when started (fix)
        static bool fix_mouse_click = false;
        if (!ImGui::IsMouseReleased(0) && fix_mouse_click)
        {
          is_black = true;
        }
        else
        {
          fix_mouse_click = true;
          is_black = false;
          flag = false;
        }
      }

      auto window_size_avail = ImGui::GetContentRegionAvail();

      prev_window_size = window_size;

      // update viewport for api
      Window::WindowProps::ViewPort* app_viewport = &MX_WINDOW->m_Props.m_Viewport;

      if (aspect_free)
      {
        app_viewport->m_Viewport_min_x = static_cast<int>(window_pos.x);
        app_viewport->m_Viewport_min_y = static_cast<int>(MX_WINDOW->m_Props.m_Height - (window_size.y + window_pos.y));

        app_viewport->m_Viewport_max_x = static_cast<int>(window_size.x);
        app_viewport->m_Viewport_max_y = static_cast<int>(window_size.y);
      }
      else if (aspect_4_3)
      {
        app_viewport->m_Viewport_min_x = static_cast<int>(window_pos.x);
        app_viewport->m_Viewport_min_y = static_cast<int>(MX_WINDOW->m_Props.m_Height - (window_size.y + window_pos.y));

        int max_y = static_cast<int>((window_size.x / 4.0f) * 3.0f);
        
        // viewport can not be maximized on x axis because window height is too small
        if (max_y > window_size_avail.y)
        {
          app_viewport->m_Viewport_max_x = static_cast<int>((window_size_avail.y / 3.0f) * 4.0f);
          app_viewport->m_Viewport_max_y = static_cast<int>(window_size.y);
          window_size_avail.x = static_cast<float>(app_viewport->m_Viewport_max_x);
        }
        else
        {
          app_viewport->m_Viewport_max_y = max_y;
          window_size_avail.y = static_cast<float>(max_y);
        }
      }
      else if (aspect_16_9)
      {
        app_viewport->m_Viewport_min_x = static_cast<int>(window_pos.x);
        app_viewport->m_Viewport_min_y = static_cast<int>(MX_WINDOW->m_Props.m_Height - (window_size.y + window_pos.y));

        int max_y = static_cast<int>((window_size.x / 16.0f) * 9.0f);

        // viewport can not be maximized on x axis because window height is too small
        if (max_y > window_size_avail.y)
        {
          app_viewport->m_Viewport_max_x = static_cast<int>((window_size_avail.y / 9.0f) * 16.0f);
          app_viewport->m_Viewport_max_y = static_cast<int>(window_size.y);
          window_size_avail.x = static_cast<float>(app_viewport->m_Viewport_max_x);
        }
        else
        {
          app_viewport->m_Viewport_max_y = max_y;
          window_size_avail.y = static_cast<float>(max_y);
        }
      }
      else if (aspect_21_9)
      {
        app_viewport->m_Viewport_min_x = static_cast<int>(window_pos.x);
        app_viewport->m_Viewport_min_y = static_cast<int>(MX_WINDOW->m_Props.m_Height - (window_size.y + window_pos.y));

        int max_y = static_cast<int>((window_size.x / 21.0f) * 9.0f);

        // viewport can not be maximized on x axis because window height is too small
        if (max_y > window_size_avail.y)
        {
          app_viewport->m_Viewport_max_x = static_cast<int>((window_size_avail.y / 9.0f) * 21.0f);
          app_viewport->m_Viewport_max_y = static_cast<int>(window_size.y);
          window_size_avail.x = static_cast<float>(app_viewport->m_Viewport_max_x);
        }
        else
        {
          app_viewport->m_Viewport_max_y = max_y;
          window_size_avail.y = static_cast<float>(max_y);
        }
      }

      // refresh when viewport gets docked or undocked
      bool docked = ImGui::IsWindowDocked();
      static bool prev_docked = false;

      if (docked != prev_docked)
      {
        MX_GAPI->m_framebuffer.m_needs_refresh = 1;
        is_black = false;
        flag = false;
      }

      prev_docked = docked;

      // draw render preview while window size doesn't change
      if (!is_black)
      {
        m_id = (void*) MX_GAPI->m_framebuffer.m_tex;
        ImGui::Image(m_id, ImVec2(window_size_avail.x, window_size_avail.y), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
      }

    }

    ImGui_Window::end();
  }
}