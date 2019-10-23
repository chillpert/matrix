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

    MX_API bool initialize(char* name, ImGuiWindowFlags flags = 0);
    MX_API void update();

    MX_API void begin();
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