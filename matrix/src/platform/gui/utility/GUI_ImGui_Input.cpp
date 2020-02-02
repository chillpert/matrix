#include "GUI_ImGui_Input.h"

namespace MX
{
  ImGui_InputText::ImGui_InputText(const std::string& label)
  {
    m_flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue;
    m_label = label;
  }

  ImGui_InputText::ImGui_InputText(const std::string& label, ImGuiInputTextFlags flags)
  {
    m_flags = flags;
    m_label = label;
  }

  bool ImGui_InputText::render(const std::string& name)
  {
    if (name == "")
    {
      // by default always fill input field with the current name of the file
      strcpy(m_buffer, name.c_str());
    }
    
    return ImGui::InputText(m_label.c_str(), m_buffer, IM_ARRAYSIZE(m_buffer), m_flags);    
  }
}