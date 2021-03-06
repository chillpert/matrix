#ifndef EDITOR_DOCK_H
#define EDITOR_DOCK_H

#include "GUI_ImGui_Window.h"

namespace MX
{
  class Editor_Dock : public ImGui_Window, public ImGui_DockNode
  {
  public:
    MX_API Editor_Dock();
    MX_API Editor_Dock(const char* name, ImGuiWindowFlags flags = 0);

    MX_API std::pair<std::string, bool*> visibilty() override;
    MX_API void set_visibilities(std::initializer_list<std::pair<std::string, bool*>> list);
    MX_API void set_visibilities(std::pair<std::string, bool*> item);

    MX_API bool initialize(const char* name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override;
    MX_API void draw();

    bool m_opt_fullscreen;
    std::vector<std::pair<std::string, bool*>> m_visibilities;
  };
}

#endif // EDITOR_DOCK_H