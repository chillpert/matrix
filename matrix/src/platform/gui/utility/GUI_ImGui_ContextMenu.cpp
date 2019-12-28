#include "GUI_ImGui_ContextMenu.h"

namespace MX
{
  ImGui_ContextMenu::ImGui_ContextMenu(const char* name) :
    m_flags(ImGuiWindowFlags_AlwaysAutoResize |
          ImGuiWindowFlags_NoMove |
          ImGuiWindowFlags_NoResize |
          ImGuiWindowFlags_NoCollapse |
          ImGuiWindowFlags_NoTitleBar),
    m_update_mouse(true),
    m_show(false),
    m_mouse_pos(ImGui::GetMousePos()),
    m_name(name),
    m_invoked_begin(false),
    m_force_focus(true) { }

  /* 
    Every call of begin() requires call of end().
    Write the actual content of this menu in between
    both calls.
  */
  bool ImGui_ContextMenu::begin()
  {
    m_invoked_begin = true;

    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
      m_show = true;

    if (m_show)
    {
      // make sure the window always appears where you right clicked at 
      if (m_update_mouse)
      {
        m_mouse_pos = ImGui::GetMousePos();
        m_update_mouse = false;
      }

      if (ImGui::Begin(m_name, NULL, m_flags))
      {
        // move window to where you clicked
        ImGui::SetWindowPos(m_mouse_pos);

        // on first right click on header set window to being focused to avoid it being deactivated
        if (m_force_focus)
        {
          ImGui::SetWindowFocus();
          m_force_focus = false;
        }

        if (!ImGui::IsWindowFocused())
        {
          m_show = false;
          m_force_focus = true;
          m_update_mouse = true;
        }

        return true;
      }
    }

    return false;
  }

  void ImGui_ContextMenu::end()
  {
    /*
      only calls end() if begin() succeeded 
      (this fix is not necessary if user works according to imgui standards)
    */
    if (m_invoked_begin)
    {
      m_invoked_begin = false;
      ImGui::End();
    }
  }
}