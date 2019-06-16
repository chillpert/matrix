#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"
#include "matrix/src/layers/World.h"

namespace MX
{
  std::vector<std::pair<std::string, ImVec4>> logger_messages_for_gui;

  bool menubar_enabled = 1;
  bool editor_window_enabled = 1;
  bool hierarchy_window_enabled = 1;
  bool logger_window_enabled = 1;
  bool demo_window_enabled = 1;

  bool p_open_editor = 1;
  bool p_open_hierarchy = 1;
  bool p_open_logger = 1;
  bool p_open_demo = 1;

  std::vector<const char*> all_available_models = {""};
  std::vector<const char*> all_available_textures = {""};
  std::vector<const char*> all_available_shaders = {""};

  std::vector<const char*> all_current_scenes;
  std::vector<const char*> all_current_objects;

  int item_objects_to_spawn = 0;
  
  int item_objects_to_select = 0;
  int item_shaders_to_select = 0;
  int item_texture_to_select = 0;
}