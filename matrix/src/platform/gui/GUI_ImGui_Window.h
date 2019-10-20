#ifndef GUI_IMGUI_WINDOW_H
#define GUI_IMGUI_WINDOW_H

#include "stdafx.h"
#include "imgui.h"

namespace MX
{
  struct ImGui_Window
  {
    bool p_open = true;
    bool p_enabled = true;

    ImGuiWindowFlags window_flags;
  };

  struct ImGui_DockNode
  {
    ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_None;
  };
}

#endif // GUI_IMGUI_WINDOW_H