#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/event/WindowEvent.h"

namespace MX
{
  static bool no_titlebar = 0;
  static bool no_scrollbar = 0;
  static bool no_menu = 1;
  static bool no_move = 1;
  static bool no_resize = 1;
  static bool no_collapse = 1;
  static bool no_close = 1;
  static bool no_nav = 0;
  static bool no_background = 0;
  static bool no_bring_to_front = 0;
  static bool p_open = 1;

  static ImGuiWindowFlags window_flags = 0;

  void GUI_ImGui::renderEventWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin(event_window_title.c_str(), &p_open, window_flags);
    ImGui::Text(event_window_message.c_str());

    ImGui::NewLine();

    std::string buttonLabel = event_window_button + "##button labeling for event window";
    if (ImGui::Button(buttonLabel.c_str()))
      set_show_event_window(0);

    ImGui::SetWindowPos(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 2.0f - middle_offset_x / 2.0f, float (Application::get().m_Window->m_Props.m_Height) / 2.0f - middle_offset_y / 2.0f));
    ImGui::SetWindowSize(ImVec2(middle_offset_x, middle_offset_y));

    ImGui::End();
  #endif
  }

  void GUI_ImGui::renderInputWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin(input_window_title.c_str(), &p_open, window_flags);
    ImGui::Text(input_window_message.c_str());

    switch (currentInputType)
    {
      // string
      case mx_name:
      {
        static char input[128];
        try 
        {
          ImGui::InputText("##type in name for object to spawn", input, IM_ARRAYSIZE(input));
        }
        catch (std::exception e)
        {
          MX_FATAL("MX: GUI: Input Window: " + std::string(e.what()));
        }

        if (ImGui::Button("confirm##confirm naming"))
        {
          std::vector<std::string> active_objects_s;
          World::get().m_ActiveScene->m_Sg.getAllObjects(&active_objects_s, World::get().m_ActiveScene->m_Sg.m_Root);
          for (const std::string &it : active_objects_s)
          {
            if (it == input)
            {
              event_window_title = "Warning";
              event_window_message = "This name is already being used";
              event_window_button = "Confirm";
              set_show_event_window(1);
              break;
            }
          }
          if (!strlen(input) == 0 && !get_show_event_window())
          {
            World::get().m_ActiveScene->push(input, all_available_models[item_objects_to_spawn] + std::string(".obj"), active_objects_s.at(item_objects_to_select));
            item_objects_to_spawn = 0;
            set_show_input_window(0);
            memset(&input[0], 0, sizeof(input));
          }
        }
        break;
      }
      // two integer
      case mx_resolution:
      {
        static int input[2];
        try
        {
          ImGui::InputInt2("##resolution input int2", input, IM_ARRAYSIZE(input));
        }
        catch(const std::exception& e)
        {
          MX_FATAL("MX: GUI: Resolution Input Window: " + std::string(e.what()));
        }
    
        if (ImGui::Button("confirm##confirm resolution input"))
        {
          if (input[0] > 1920 || input[1] > 1080 || input[0] < 200 || input[1] < 200)
          {
            event_window_title = "Warning";
            event_window_message = "Invalid resolution";
            set_show_event_window(1);
          }
          else
          {
            WindowResized event(input[0], input[1]);
            event.handle();
            LOGEVENT(event);
    
            if (input[0] == 1920 && input[1] == 1080)
              Application::get().m_Window->m_Props.m_FullScreen = 1;
    
            set_show_input_window(0);
          }      
        }

        ImGui::SameLine();

        if (ImGui::Button("cancel"))
          set_show_input_window(0);

        break;
      }
      default:
        break;
    }

    ImGui::SetWindowPos(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 2.0f - middle_offset_x / 2.0f, float (Application::get().m_Window->m_Props.m_Height) / 2.0f - middle_offset_y / 2.0f));
    ImGui::SetWindowSize(ImVec2(middle_offset_x, middle_offset_y));

    ImGui::End();
  #endif
  }
}