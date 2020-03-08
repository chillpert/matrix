#ifndef EDITOR_EXPLORER_H
#define EDITOR_EXPLORER_H

#include "GUI_ImGui_Utility.h"

namespace MX
{
  class Editor_Explorer : public ImGui_Window
  {
  public:
    MX_API Editor_Explorer(const char* name, ImGuiWindowFlags flags = 0);

    MX_API bool initialize(const char* name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override; 

  private:
    MX_API void update_directory(const char* path);
    MX_API void render_directory_compact();
    MX_API void render_directory_large();
    MX_API void refresh_directory();
    MX_API void handle_file_interaction();

    MX_API void setup_drag_drop_source(const std::string& file_name, const std::string& file_path);

  private:
    std::string current_path = MX_RESOURCES;
    const std::string lowest_path = MX_RESOURCES;
    
    // parameters: file_name, full_path, is_directory
    std::vector<std::tuple<std::string, std::string, bool>> m_items_in_directory;
    bool m_update_items_in_directory = true;

    const float m_menu_icon_size = 15.0f;
    const float m_small_icon_size = 20.0f;
    const float m_large_icon_size = 50.0f;

  public:
    std::vector<std::string> m_selection;
  };
}

#endif // EDITOR_EXPLORER_H