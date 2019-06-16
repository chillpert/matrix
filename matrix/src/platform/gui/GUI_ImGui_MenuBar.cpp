#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/event/WindowEvent.h"

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
  // static bool popup_no_close = 0;
  static bool popup_no_nav = 0;
  static bool popup_no_background = 0;
  static bool popup_no_bring_to_front = 1;
  static bool popup_no_autoresize = 0;
  // static bool popup_p_open = 1;

  static bool first_run = 1;
  static bool dockspace_p_open = 1;

  static void render_about_popup();
  static void render_set_resolution_popup();

  void GUI_ImGui::renderDockSpace()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
      ImGuiViewport* viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->Pos);
      ImGui::SetNextWindowSize(viewport->Size);
      ImGui::SetNextWindowViewport(viewport->ID);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
      window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspace_p_open, window_flags);
    ImGui::PopStyleVar();

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (opt_fullscreen)
      ImGui::PopStyleVar(2);

    ImGui::End();

  #endif
  }

  void GUI_ImGui::renderViewport()
  {
  #ifdef MX_IMGUI_ACTIVE
    static ImGuiWindowFlags window_flags = 0;
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 0;
    // static bool no_close = 0;
    static bool no_nav = 0;
    static bool no_background = 1;
    static bool no_bring_to_front = 0;
    static bool no_autoresize = 0;
    static bool p_open = 1;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus; 
    if (no_autoresize)      window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    
    ImGui::Begin("ViewPort", &p_open_viewport, window_flags);

    if (first_run)
    {
      ImGui::SetWindowPos(ImVec2(0, 19));
      ImGui::SetWindowSize(ImVec2(
        Application::get().m_Window->m_Props.m_ViewportX,
        Application::get().m_Window->m_Props.m_ViewportY - 19
      ));
      first_run = 0;
    }

    auto window_size = ImGui::GetWindowSize(); // 853, 581
    auto window_pos = ImGui::GetWindowPos(); // 0, 19

    Application::get().m_Window->m_Props.m_CornerX = window_pos.x; // 0
    Application::get().m_Window->m_Props.m_CornerY = window_size.y + window_pos.y; // 19

    Application::get().m_Window->m_Props.m_ViewportX = window_size.x; // 853
    Application::get().m_Window->m_Props.m_ViewportY = window_size.y; // 581
    
    ImGui::End();
  #endif
  }

  void GUI_ImGui::renderMenuBar()
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
/*
        if (!viewport_enabled)
        {
          if (ImGui::MenuItem("show viewport", "CTRL+P"))
          {
            viewport_enabled = 1;
            p_open_viewport = 1;
          }
        }
        else
        {
          if (ImGui::MenuItem("hide viewport", "CTRL+P"))
          {
            viewport_enabled = 0;
            p_open_viewport = 0;
          }
        }
*/      
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

        ImGui::Separator();

        if (logger_window_enabled || hierarchy_window_enabled || editor_window_enabled || demo_window_enabled)
        {
          if (ImGui::MenuItem("hide all", "CTRL+G"))
          {
            logger_window_enabled = 0;
            p_open_logger = 0;
            hierarchy_window_enabled = 0;
            p_open_hierarchy = 0;
            editor_window_enabled = 0;
            p_open_editor = 0;
            demo_window_enabled = 0;
            p_open_demo = 0;
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
            demo_window_enabled = 1;
            p_open_demo = 1;
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
          LOGEVENT(event);
    
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