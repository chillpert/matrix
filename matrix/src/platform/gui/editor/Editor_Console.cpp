#include "Editor_Console.h"
#include "Logger.h"

namespace MX
{
  bool Editor_Console::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
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

        ImGui::EndMenuBar();
      }

      static ImGuiTextFilter filter;
      filter.Draw("##console filter label", ImGui::GetContentRegionAvailWidth());

      ImGui::Separator();
      
      for (auto &it : Logger::get_messages_gui())
      {
        if (std::get<2>(it) == mx_info && !messages_info)
          continue;

        if (std::get<2>(it) == mx_warn && !messages_warn)
          continue;

        if (std::get<2>(it) == mx_fatal && !messages_fatal)
          continue;

        if (std::get<2>(it) == mx_success && !messages_success)
          continue;
        
        if (filter.PassFilter(std::get<0>(it).c_str()))
          ImGui::TextColored(std::get<1>(it), std::get<0>(it).c_str());
      }

      ImGui_Window::end();
    }
  }
}