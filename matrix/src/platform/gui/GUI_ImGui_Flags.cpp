#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"
#include "matrix/src/layers/World.h"

namespace MX
{
  InputTypes currentInputType = mx_name;
  SelectionTypes currentSelectionType = mx_null;

  const std::string default_window_title = "undefined window title";
  const std::string default_window_message = "undefined window message";
  const std::string default_button_label = "undefined button label";

  std::string event_window_title = default_window_title;
  std::string event_window_message = default_window_message;
  std::string event_window_button = default_button_label;

  std::vector<std::pair<std::string, ImVec4>> logger_messages_for_gui;

  bool event_window_enabled = 0;
  bool input_window_enabled = 0;
  bool selection_window_enabled = 0;
  bool menubar_enabled = 1;
  bool editor_window_enabled = 1;
  bool hierarchy_window_enabled = 1;
  bool logger_window_enabled = 1;

  bool p_open_editor = 1;
  bool p_open_hierarchy = 1;
  bool p_open_logger = 1;
  bool p_open_event = 1;

  std::vector<const char*> all_available_models = {""};
  std::vector<const char*> all_available_textures = {""};
  std::vector<const char*> all_available_shaders = {""};
  std::vector<const char*> all_current_scenes;
  std::vector<std::string> active_objects_s;

  int item_objects_to_spawn = 0;
  
  int item_objects_to_select = 0;
  int item_shaders_to_select = 0;
  int item_texture_to_select = 0;

  void reset_window_naming()
  {
    event_window_title = default_window_title;
    event_window_message = default_window_message;
    event_window_button = default_button_label;
  }
}