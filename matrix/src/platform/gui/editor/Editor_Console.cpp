#include "Editor_Console.h"
#include "Logger.h"

namespace MX
{
  Editor_Console::Editor_Console(const std::string& name, ImGuiWindowFlags flags)
  {
    initialize(name, flags);
  }

  bool Editor_Console::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    m_clear_popup.initialize("Warning##Clear Console", ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Console::update()
  {
    return ImGui_Window::update();
  }

  void Editor_Console::render()
  {
    if (ImGui_Window::begin())
    {
      static bool fully_colored = false;

      static bool messages_info = true;
      static bool messages_warn = true;
      static bool messages_fatal = true;
      static bool messages_success = true;

      if (ImGui::BeginMenuBar())
      {
        if (ImGui::BeginMenu("Type"))
        {
          ImGui::MenuItem("Info", NULL, &messages_info);
          ImGui::MenuItem("Warn", NULL, &messages_warn);
          ImGui::MenuItem("Success", NULL, &messages_success);
          ImGui::MenuItem("Fatal", NULL, &messages_fatal);
          ImGui::Separator();
          if (ImGui::MenuItem("Reset"))
          {
            messages_info = true;
            messages_warn = true;
            messages_fatal = true;
            messages_success = true;
          }

          ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Color"))
        {
          ImGui::MenuItem("All", NULL, &fully_colored);

          ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
      }

      static ImGuiTextFilter filter;
      float avail_width = ImGui::GetContentRegionAvailWidth();
      filter.Draw("##console filter label", avail_width * 4.0f / 5.0f);

      ImGui::SameLine();
      if (ImGui::Button("Clear##Confirm Clear Console Button", ImVec2(avail_width / 5.0f - 8.0f, 0.0f)))
        m_clear_popup.open();

      ImGui::Separator();
      
      for (auto &it : Logger::get_messages_gui())
      {
        if (filter.PassFilter(it.first.c_str()))
        {
          switch (it.second)
          {
            case mx_info:
            {
              if (!messages_info)
                break;
              else
              {
                if (fully_colored)
                  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), it.first.c_str());
                else
                  ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), it.first.c_str());              
                break;
              }
            }
            case mx_warn:
            {
              if (!messages_warn)
                break;
              else
              {
                if (fully_colored)
                  ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), it.first.c_str());
                else
                  ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), it.first.c_str());                            
                break;
              }            
            }
            case mx_fatal:
            {
              if (!messages_fatal)
                break;
              else
              {
                if (fully_colored)
                  ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), it.first.c_str());
                else
                  ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), it.first.c_str());
                break;
              }
            }
            case mx_success:
            {
              if (!messages_success)
                break;
              else
              {
                if (fully_colored)
                  ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), it.first.c_str());
                else
                  ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), it.first.c_str());        
                break;
              }
            }
            default:
            break;
          }
        }
      }
    }

    // clear console confirmation popup
    if (m_clear_popup.begin())
    {
      ImGui::Text("Do you really want to clear the console?");

      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      float avail_width = ImGui::GetContentRegionAvailWidth();
      if (ImGui::Button("Yes", ImVec2(avail_width / 2.0f - 5.0f, 0.0f)))
      {
        ImGui::CloseCurrentPopup();
        Logger::get_messages_gui().clear();
      }

      ImGui::SameLine();

      if (ImGui::Button("No", ImVec2(avail_width / 2.0f - 5.0f, 0.0f)))
        ImGui::CloseCurrentPopup();


      m_clear_popup.end();
    }

    ImGui_Window::end();
  }
}