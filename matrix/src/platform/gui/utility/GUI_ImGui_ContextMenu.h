#ifndef GUI_IMGUI_CONTEXTMENU_H
#define GUI_IMGUI_CONTEXTMENU_H

#include "stdafx.h"

namespace MX
{
  class ImGui_ContextMenu
  {
  public:
    MX_API ImGui_ContextMenu(const char* name);

    MX_API bool begin();
    MX_API void end();

    ImGuiWindowFlags m_flags;

  private:
    MX_API bool is_clicked();

    bool m_update_mouse;
    bool m_show;
    ImVec2 m_mouse_pos;
    const char* m_name;
    bool m_invoked_begin;
    bool m_force_focus;
  };
}

#endif // GUI_IMGUI_CONTEXTMENU_H