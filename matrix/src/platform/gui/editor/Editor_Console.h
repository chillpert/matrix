#ifndef EDITOR_CONSOLE_H
#define EDITOR_CONSOLE_H

#include "GUI_ImGui_Window.h"

namespace MX
{
  class Editor_Console : public ImGui_Window
  {
  public:
    MX_API Editor_Console() = default;

    MX_API bool initialize(const std::string& name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override;
  };
}

#endif // EDITOR_CONSOLE_H