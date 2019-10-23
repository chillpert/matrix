#ifndef GUI_IMGUI_WINDOW_H
#define GUI_IMGUI_WINDOW_H

#include "stdafx.h"
#include "imgui.h"

namespace MX
{
  class ImGui_Window
  {
  public:
    ImGui_Window() = default;

    MX_API void update();

    bool p_open = true;
    bool p_enabled = true;

    char* m_name = "undef";

    ImGuiWindowFlags window_flags;
  };

  struct ImGui_DockNode
  {
    ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_None;
  };
}

#endif // GUI_IMGUI_WINDOW_H