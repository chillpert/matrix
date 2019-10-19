#ifndef EDITOR_DOCK_H
#define EDITOR_DOCK_H

#include "stdafx.h"
#include "imgui.h"
#include "GUI_ImGui_Window.h"

namespace MX
{
  class Editor_Dock
  {
  public:
    MX_API Editor_Dock() = default;

    MX_API void initialize();
    MX_API void render();

    ImGui_Window m_window;
  };
}

#endif // EDITOR_DOCK_H