#include "Editor_Editor.h"
#include "Event.h"
#include "KeyboardEvent.h"

namespace MX
{
  Editor_Editor::Editor_Editor(const char* name, ImGuiWindowFlags flags)
  {
    initialize(name, flags);
  }

  bool Editor_Editor::initialize(const char* name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Editor::update()
  {
    return ImGui_Window::update();
  }

  void Editor_Editor::render()
  {
    if (ImGui_Window::begin())
    {
      if (ImGui::BeginMenuBar())
      {
        if (ImGui::BeginMenu("File"))
        {
          if (ImGui::MenuItem("Save"))
          {
            if (Utility::write_file(m_text, m_active_path))
            {
              MX_SUCCESS_LOG("MX: GUI: Editor: Saved file: " + m_active_path);
            }
          }

          ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
      }

      static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CtrlEnterForNewLine;
      ImGui::InputTextMultiline("##source", m_text, IM_ARRAYSIZE(m_text), ImVec2(-1, -1), flags);
    }
    ImGui_Window::end();
  }

  void Editor_Editor::set_input(const std::string& path)
  {
    m_active_path = path;

    std::string temp = Utility::parse_file(path);
    strcpy(m_text, temp.c_str());
  }
}