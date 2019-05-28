#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/event/WindowEvent.h"

namespace MX
{
  void GUI_ImGui::renderEventWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    ImGui::Begin(event_window_title.c_str());
    ImGui::Text(event_window_message.c_str());
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
    ImGui::Begin(input_window_title.c_str());
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
            World::get().m_ActiveScene->push(input, all_available_models[item_objects_to_spawn] + std::string(".obj"));
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