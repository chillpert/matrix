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
      static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CtrlEnterForNewLine;
      
      
      
      ImGui::InputTextMultiline("##source", m_text, IM_ARRAYSIZE(m_text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
    }
    ImGui_Window::end(); 
  }
}