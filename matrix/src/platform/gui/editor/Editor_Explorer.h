#ifndef EDITOR_EXPLORER_H
#define EDITOR_EXPLORER_H

#include "GUI_ImGui_Utility.h"

namespace MX
{
  class Editor_Explorer : public ImGui_Window
  {
  public:
    MX_API Editor_Explorer(const std::string& name, ImGuiWindowFlags flags = 0);

    MX_API bool initialize(const std::string& name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override; 

    MX_API void load_directory(const char* path);
    MX_API void setup_drag_drop_source(const std::string& file_name, const std::string& file_path);

    std::vector<std::string> m_selection;

  private:
    ImGui_Popup m_popup_delete;

    std::string current_path = MX_RESOURCES;
    const std::string lowest_path = MX_RESOURCES;
  };
}

#endif // EDITOR_EXPLORER_H