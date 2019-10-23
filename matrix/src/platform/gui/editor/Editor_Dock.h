#ifndef EDITOR_DOCK_H
#define EDITOR_DOCK_H

#include "GUI_ImGui_Window.h"

namespace MX
{
  class Editor_Dock : public ImGui_Window, public ImGui_DockNode
  {
  public:
    MX_API Editor_Dock();

    MX_API bool initialize();
    MX_API void update();
    MX_API void render();

    bool m_opt_fullscreen;
  };
}

#endif // EDITOR_DOCK_H