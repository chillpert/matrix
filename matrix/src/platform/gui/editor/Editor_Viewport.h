#ifndef EDITOR_VIEWPORT_H
#define EDITOR_VIEWPORT_H

#include "GUI_ImGui_Window.h"

namespace MX
{
  class Editor_Viewport : public ImGui_Window
  {
  public:
    MX_API Editor_Viewport() = default;
    MX_API Editor_Viewport(const char* name, ImGuiWindowFlags flags = 0);

    MX_API bool initialize(const char* name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override;

    // ID and dimensions of framebuffer
    ImTextureID m_id;
    float m_width;
    float m_height;
  };
}

#endif // EDITOR_VIEWPORT_H