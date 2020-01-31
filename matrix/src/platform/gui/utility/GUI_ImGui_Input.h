#ifndef GUI_IMGUI_INPUT_H
#define GUI_IMGUI_INPUT_H

#include "stdafx.h"
#include "imgui.h"

namespace MX
{
  class ImGui_InputText
  {
  public:
    MX_API ImGui_InputText(const std::string& label);
    MX_API ImGui_InputText(const std::string& label, ImGuiInputTextFlags flags);

    MX_API bool render(const std::string& name = "__UNDEF__");
  
    char m_buffer[128];

  private:
    ImGuiInputTextFlags m_flags;
    std::string m_label;
  };
}

#endif // GUI_IMGUI_INPUT_TEXT_H