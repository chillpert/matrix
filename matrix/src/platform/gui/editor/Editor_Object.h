#ifndef EDITOR_OBJECT_H
#define EDITOR_OBJECT_H

#include "GUI_ImGui_Window.h"
#include "Editor_Global.h"

namespace MX
{
  class Editor_Object : public ImGui_Window, public Editor_Global
  {
  public:
    MX_API Editor_Object() = default;
    MX_API Editor_Object(const std::string& name, ImGuiWindowFlags flags = 0);
    
    MX_API bool initialize(const std::string& name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override;
  };
}

#endif // EDITOR_OBJECT_H