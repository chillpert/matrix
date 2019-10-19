#ifndef GUI_IMGUI_WINDOW_H
#define GUI_IMGUI_WINDOW_H

#include "stdafx.h"
#include "imgui.h"

namespace MX
{
  // all flags are enabled by default
  class ImGui_Window
  {
  public:
    MX_API ImGui_Window();

    MX_API void no_titlebar();
    MX_API void no_scrollbar();
    MX_API void no_menu();
    MX_API void no_move();
    MX_API void no_resize();
    MX_API void no_collapse();
    MX_API void no_navigation();
    MX_API void no_background();
    MX_API void no_bring_to_front();

    MX_API inline ImGuiWindowFlags get_flag() const { return flags; }

    bool p_open;
    bool p_enabled;

  private:
    ImGuiWindowFlags flags;
  };
}

#endif // GUI_IMGUI_WINDOW_H