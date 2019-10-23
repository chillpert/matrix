#ifndef GUI_IMGUI_WINDOW_H
#define GUI_IMGUI_WINDOW_H

#include "stdafx.h"
#include "imgui.h"

namespace MX
{
  class ImGui_Window
  {
  public:
    MX_API ImGui_Window() = default;

    MX_API bool initialize(char* name, ImGuiWindowFlags flags = 0);

    // updates window size if too big
    MX_API void update();

    // invokes imgui begin
    MX_API void begin();
    // invokes imgui end
    MX_API void end();

    MX_API void add_flags(ImGuiWindowFlags flags);
    MX_API void set_flags(ImGuiWindowFlags flags);

  private:
    bool p_enabled = true;
    bool p_open = true;

    ImGuiWindowFlags m_window_flags;
  
    char* m_name = "undef";
  };

  struct ImGui_DockNode
  {
    ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_None;
  };
}

#endif // GUI_IMGUI_WINDOW_H