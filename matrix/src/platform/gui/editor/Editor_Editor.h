#ifndef EDITOR_EDITOR_H
#define EDITOR_EDITOR_H

#include "GUI_ImGui_Window.h"

namespace MX
{
  class Editor_Editor : public ImGui_Window
  {
  public:
    MX_API Editor_Editor() = default;
    MX_API Editor_Editor(const char* name, ImGuiWindowFlags flags = 0);

    MX_API bool initialize(const char* name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override;

    MX_API void set_input(const std::string& path);

    char m_text[1024 * 16];
    std::string m_active_path = "";
  };
}

#endif // EDITOR_EDITOR_H