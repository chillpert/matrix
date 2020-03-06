#include "GUI_ImGui_Popup.h"

namespace MX
{
  ImGui_Popup::ImGui_Popup(const char* name, ImGuiWindowFlags flags)
    : ImGui_Window(name, flags) { }

  void ImGui_Popup::open()
  {
    ImGui::OpenPopup(m_name);
  }

  void ImGui_Popup::close()
  {
    ImGui::CloseCurrentPopup();
  }

  bool ImGui_Popup::begin()
  {
    return ImGui::BeginPopup(m_name, m_window_flags);
  }

  bool ImGui_Popup::beginModal()
  {
    return ImGui::BeginPopupModal(m_name, NULL, m_window_flags);
  }

  void ImGui_Popup::end()
  {
    ImGui::EndPopup();
  }
}