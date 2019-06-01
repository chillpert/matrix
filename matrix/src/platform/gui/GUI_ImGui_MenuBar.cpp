#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/event/WindowEvent.h"

namespace MX
{
  void GUI_ImGui::renderMenuBar()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::BeginMainMenuBar())
    {     
      if (ImGui::BeginMenu("File"))
      {
        if (ImGui::MenuItem("New")) {}
        if (ImGui::MenuItem("Load")) {}
        ImGui::Separator();
        if (ImGui::MenuItem("Save")) {}
        if (ImGui::MenuItem("Save as")) {}

        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Edit"))
      {
        if (ImGui::MenuItem("Undo", "CTRL+Z", false, false)) {}
        if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
        ImGui::Separator();
        if (ImGui::MenuItem("Cut", "CTRL+X")) {}
        if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        if (ImGui::MenuItem("Paste", "CTRL+V")) {}
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Window"))
      {
        if (!editor_window_enabled)
        {
          if (ImGui::MenuItem("show editor", "CTRL+E"))
          {
            editor_window_enabled = 1;
            p_open_editor = 1;
          }
        }
        else
        {
          if (ImGui::MenuItem("hide editor", "CTRL+E"))
          {
            editor_window_enabled = 0;
            p_open_editor = 0;
          }
        }

        if (!hierarchy_window_enabled)
        {
          if (ImGui::MenuItem("show hierarchy", "CTRL+H"))
          {
            hierarchy_window_enabled = 1;
            p_open_hierarchy = 1;
          }
        }
        else
        {
          if (ImGui::MenuItem("hide hierarchy", "CTRL+H"))
          {
            hierarchy_window_enabled = 0;
            p_open_hierarchy = 0;
          }
        }

        if (!logger_window_enabled)
        {
          if (ImGui::MenuItem("show logger", "CTRL+L"))
          {
            logger_window_enabled = 1;
            p_open_logger = 1;
          }
        }
        else
        {
          if (ImGui::MenuItem("hide logger", "CTRL+L"))
          {
            logger_window_enabled = 0;
            p_open_logger = 0;
          }
        }

        ImGui::Separator();

        if (logger_window_enabled || hierarchy_window_enabled || editor_window_enabled)
        {
          if (ImGui::MenuItem("hide all", "CTRL+G"))
          {
            logger_window_enabled = 0;
            p_open_logger = 0;
            hierarchy_window_enabled = 0;
            p_open_hierarchy = 0;
            editor_window_enabled = 0;
            p_open_editor = 0;
          }
        }
        else
        {
          if (ImGui::MenuItem("show all", "CTRL+G"))
          {
            logger_window_enabled = 1;
            p_open_logger = 1;
            hierarchy_window_enabled = 1;
            p_open_hierarchy = 1;
            editor_window_enabled = 1;
            p_open_editor = 1;
          }
        }

        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Settings"))
      {
        if (ImGui::MenuItem("toggle fullscreen", "CTRL+F"))
        {
          if (Application::get().m_Window->m_Props.m_FullScreen == 0)
          {
            WindowResized event(1920, 1080);
            event.handle();
            LOGEVENT(event);
            Application::get().m_Window->m_Props.m_FullScreen = 1;
          }
          else
          {
            WindowResized event(initial_window_width, initial_window_height);
            event.handle();
            LOGEVENT(event);
            Application::get().m_Window->m_Props.m_FullScreen = 0;
          }
        }
        if (ImGui::MenuItem("set resolution"))
        {
          event_window_title = "Info";
          event_window_message = "Please enter a resolution";
          input_window_enabled = 1;
          currentInputType = mx_resolution;
        }
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Help"))
      {
        if (ImGui::MenuItem("About"))
        {
          event_window_title = "About";
          event_window_message = "I do not know what to say\nAnyway ... how are you doing?";
          event_window_button = "I WANT TO DIE";
          event_window_enabled = 1;
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  #endif
  }
}