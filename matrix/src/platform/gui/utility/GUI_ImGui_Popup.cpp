#include "GUI_ImGui_Popup.h"
#include "Application.h"

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

  ImGui_PopupHoverInfo::ImGui_PopupHoverInfo()
    : m_condition_length(1.0f), m_show_hover_info(false) { }

  ImGui_PopupHoverInfo::ImGui_PopupHoverInfo(const char* name, ImGuiWindowFlags flags)
    : ImGui_Popup(name, flags), m_condition_length(1.0f), m_show_hover_info(false) { }

  void ImGui_PopupHoverInfo::render(const char* message, bool condition)
  {
    if (condition && !m_show_hover_info)
    {
      if (m_initial_condition)
      {
        m_time_on_condition = MX_WINDOW->m_Props.m_Time;
        m_initial_condition = false;
      }

      if (MX_WINDOW->m_Props.m_Time - m_time_on_condition > m_condition_length)
      {
        m_initial_condition = true;
        m_time_on_condition = 0.0f;
        m_show_hover_info = true;
      }
    }

    if (m_show_hover_info)
    {
      m_show_hover_info = false;
      ImGui_Popup::open();
    }

    if (ImGui_Popup::begin())
    {
      ImGui::Text(message);
      ImGui_Popup::end();
    }
  }
}