#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"
#include "matrix/src/Application.h"

namespace MX
{
  static bool no_titlebar = 0;
  static bool no_scrollbar = 0;
  static bool no_menu = 0;
  static bool no_move = 1;
  static bool no_resize = 1;
  static bool no_collapse = 1;
  static bool no_close = 0;
  static bool no_nav = 0;
  static bool no_background = 0;
  static bool no_bring_to_front = 0;

  // will display all messages by default
  static logger_message_type message_type = mx_all;

  static bool all_flag = 0;
  static bool info_flag = 1;
  static bool warn_flag = 1;
  static bool fatal_flag = 1;
  static bool success_flag = 1;

  void toggle_flags()
  {
    switch (message_type)
    {
      case mx_all:
      {
        all_flag = 0;
        info_flag = 1;
        warn_flag = 1;
        fatal_flag = 1;
        success_flag = 1;
        break;
      }
      case mx_info:
      {
        all_flag = 1;
        info_flag = 0;
        warn_flag = 1;
        fatal_flag = 1;
        success_flag = 1;
        break;
      }
      case mx_warn:
      {
        all_flag = 1;
        info_flag = 1;
        warn_flag = 0;
        fatal_flag = 1;
        success_flag = 1;
        break;
      }
      case mx_fatal:
      {
        all_flag = 1;
        info_flag = 1;
        warn_flag = 1;
        fatal_flag = 0;
        success_flag = 1;
        break;
      }
      case mx_success:
      {
        all_flag = 1;
        info_flag = 1;
        warn_flag = 1;
        fatal_flag = 1;
        success_flag = 0;
        break;
      }
    }
  }

  void GUI_ImGui::renderLoggerWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    static ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Logger", &p_open_logger, window_flags);

    if (ImGui::BeginMenuBar())
    {
      if (ImGui::MenuItem("All", "", true, all_flag))
        message_type = mx_all;

      if (ImGui::MenuItem("Info", "", true, info_flag))
        message_type = mx_info;

      if (ImGui::MenuItem("Warn", "", true, warn_flag))
        message_type = mx_warn;

      if (ImGui::MenuItem("Fatal", "", true, fatal_flag))
        message_type = mx_fatal;

      if (ImGui::MenuItem("Success", "", true, success_flag))
        message_type = mx_success;

      ImGui::EndMenuBar();
    }

    toggle_flags();

    switch (message_type)
    {
      case mx_all:
      {
        for (auto &it : logger_messages_for_gui)
          ImGui::TextColored(it.second, it.first.c_str());
        break;
      }
      case mx_info:
      {
        for (auto &it : logger_messages_for_gui)
        {
          if (it.second.x == 1.0f && it.second.y == 1.0f && it.second.z == 1.0f)
            ImGui::TextColored(it.second, it.first.c_str());
          else
            continue;
        }
        break;
      }
      case mx_warn:
      {
        for (auto &it : logger_messages_for_gui)
        {
          if (it.second.x == 1.0f && it.second.y == 1.0f && it.second.z == 0.0f)
            ImGui::TextColored(it.second, it.first.c_str());
          else
            continue;
        }
        break;
      }
      case mx_fatal:
      {
        for (auto &it : logger_messages_for_gui)
        {
          if (it.second.x == 1.0f && it.second.y == 0.0f && it.second.z == 0.0f)
            ImGui::TextColored(it.second, it.first.c_str());
          else
            continue;
        }
        break;
      }
      case mx_success:
      {
        for (auto &it : logger_messages_for_gui)
        {
          if (it.second.x == 0.0f && it.second.y == 1.0f && it.second.z == 0.0f)
            ImGui::TextColored(it.second, it.first.c_str());
          else
            continue;
        }
        break;
      }
    }

    if (!p_open_logger)
      logger_window_enabled = 0;

    if (editor_window_enabled || hierarchy_window_enabled)
    {
      ImGui::SetWindowPos(
        ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 5.0f, 
               float (Application::get().m_Window->m_Props.m_Height) - float (Application::get().m_Window->m_Props.m_Height) / 4.0f)
      );
      ImGui::SetWindowSize(
        ImVec2(float (Application::get().m_Window->m_Props.m_Width) - float (Application::get().m_Window->m_Props.m_Width) / 5.0f,
               float (Application::get().m_Window->m_Props.m_Height) / 4.0f)
      );
    }
    else if (!editor_window_enabled && !hierarchy_window_enabled)
    {
      ImGui::SetWindowPos(
        ImVec2(0.0f,
               float (Application::get().m_Window->m_Props.m_Height) - float (Application::get().m_Window->m_Props.m_Height) / 4.0f)
      );
      ImGui::SetWindowSize(
        ImVec2(float (Application::get().m_Window->m_Props.m_Width),
               float (Application::get().m_Window->m_Props.m_Height) / 4.0f)
      );
    }
        
    ImGui::End();
  #endif
  }
}