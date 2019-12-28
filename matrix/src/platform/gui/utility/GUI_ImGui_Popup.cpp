#include "GUI_ImGui_Popup.h"

namespace MX
{
  void ImGui_Popup::open()
  {
    ImGui::OpenPopup(m_name.c_str());
  }

  bool ImGui_Popup::begin()
  {
    return ImGui::BeginPopupModal(m_name.c_str(), NULL, m_window_flags);
  }

  void ImGui_Popup::end()
  {
    ImGui::EndPopup();
  }


}