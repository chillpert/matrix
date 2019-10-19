#include <GUI_Editor.h>
#include <Application.h>
#include <WindowEvent.h>

namespace MX
{
  static bool show_about_popup = 0;
  static bool show_set_resolution_popup = 0;

  static bool resolution_accepted = 1;

  // pop_flags
  static ImGuiWindowFlags popup_flags = 0;
  static bool popup_no_titlebar = 0;
  static bool popup_no_scrollbar = 0;
  static bool popup_no_menu = 1;
  static bool popup_no_move = 1;
  static bool popup_no_resize = 1;
  static bool popup_no_collapse = 1;
  static bool popup_no_nav = 0;
  static bool popup_no_background = 0;
  static bool popup_no_bring_to_front = 1;
  static bool popup_no_autoresize = 0;

  static void render_about_popup();
  static void render_set_resolution_popup();

  void GUI_Editor::renderMenuBar()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (popup_no_titlebar)        popup_flags |= ImGuiWindowFlags_NoTitleBar;
    if (popup_no_scrollbar)       popup_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!popup_no_menu)           popup_flags |= ImGuiWindowFlags_MenuBar;
    if (popup_no_move)            popup_flags |= ImGuiWindowFlags_NoMove;
    if (popup_no_resize)          popup_flags |= ImGuiWindowFlags_NoResize;
    if (popup_no_collapse)        popup_flags |= ImGuiWindowFlags_NoCollapse;
    if (popup_no_nav)             popup_flags |= ImGuiWindowFlags_NoNav;
    if (popup_no_background)      popup_flags |= ImGuiWindowFlags_NoBackground;
    if (!popup_no_bring_to_front) popup_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus; 
    if (popup_no_autoresize)      popup_flags |= ImGuiWindowFlags_AlwaysAutoResize;

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
 
        if (!demo_window_enabled)
        {
          if (ImGui::MenuItem("show demo", "CTRL+D"))
          {
            demo_window_enabled = 1;
            p_open_demo = 1;
          }
        }
        else
        {
          if (ImGui::MenuItem("hide demo", "CTRL+D"))
          {
            demo_window_enabled = 0;
            p_open_demo = 0;
          }
        }

        if (!performance_monitor_enabled)
        {
          if (ImGui::MenuItem("show performance monitor", "CTRL+P"))
          {
            performance_monitor_enabled = 1;
            p_open_performance_monitor = 1;
          }
        }
        else
        {
          if (ImGui::MenuItem("hide performance monitor", "CTRL+P"))
          {
            performance_monitor_enabled = 0;
            p_open_performance_monitor = 0;
          }
        }

        ImGui::Separator();

        if (logger_window_enabled || hierarchy_window_enabled || demo_window_enabled || performance_monitor_enabled)
        {
          if (ImGui::MenuItem("hide all", "CTRL+G"))
          {
            logger_window_enabled = 0;
            p_open_logger = 0;
            hierarchy_window_enabled = 0;
            p_open_hierarchy = 0;
            demo_window_enabled = 0;
            p_open_demo = 0;
            performance_monitor_enabled = 0;
            p_open_performance_monitor = 0;
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
            demo_window_enabled = 1;
            p_open_demo = 1;
            performance_monitor_enabled = 1;
            p_open_performance_monitor = 1;
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
            LOGEVENT;
            Application::get().m_Window->m_Props.m_FullScreen = 1;
          }
          else
          {
            WindowResized event(initial_window_width, initial_window_height);
            event.handle();
            LOGEVENT;
            Application::get().m_Window->m_Props.m_FullScreen = 0;
          }
        }
        if (ImGui::MenuItem("set resolution"))
          show_set_resolution_popup = 1;

        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Help"))
      {
        if (ImGui::MenuItem("About"))
          show_about_popup = 1;

        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    if (show_about_popup)
      ImGui::OpenPopup("About##shows information about the project");
    
    if (show_set_resolution_popup)
      ImGui::OpenPopup("Resolution##set window resolution");

    render_about_popup();
    render_set_resolution_popup();
    
  #endif
  }

  static void render_about_popup()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::BeginPopupModal("About##shows information about the project", NULL, popup_flags))
    {
      ImGui::Text("I do not know what to say\nAnyway ... how are you doing?");

      if (ImGui::Button("I want to die"))
      {
        show_about_popup = 0;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }
  #endif
  }

  static void render_set_resolution_popup()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::BeginPopupModal("Resolution##set window resolution", NULL, popup_flags))
    {
      if (resolution_accepted)
        ImGui::Text("Set resolution:");
      else
        ImGui::Text("Invalid resolution");

      static int input[2];
      ImGui::InputInt2("##resolution input int2", input, IM_ARRAYSIZE(input));
    
      if (ImGui::Button("Confirm##confirm resolution"))
      {
        if (input[0] > 1920 || input[1] > 1080 || input[0] < 200 || input[1] < 200)
          resolution_accepted = 0;
        else
        {
          WindowResized event(input[0], input[1]);
          event.handle();
          LOGEVENT;
    
          if (input[0] == 1920 && input[1] == 1080)
            Application::get().m_Window->m_Props.m_FullScreen = 1;

          resolution_accepted = 1;
          show_set_resolution_popup = 0;
          ImGui::CloseCurrentPopup();
        }
      }

      ImGui::SameLine();

      if (ImGui::Button("Cancel##cancel resolution input"))
      {
        resolution_accepted = 1;
        show_set_resolution_popup = 0;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }
  #endif
  }
}