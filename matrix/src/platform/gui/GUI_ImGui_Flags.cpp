#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"

namespace MX
{
  InputTypes currentInputType = mx_name;

  const std::string default_window_title = "undefined window title";
  const std::string default_window_message = "undefined window message";
  const std::string default_button_label = "undefined button label";

  std::string event_window_title = default_window_title;
  std::string event_window_message = default_window_message;
  std::string event_window_button = default_button_label;

  std::string input_window_title = default_window_title;
  std::string input_window_message = default_window_message;

  std::string selection_window_title = default_window_title;
  std::string selection_window_message = default_window_message;
  std::string selection_window_button = default_button_label;

  bool show_event_window = 0;
  bool show_input_window = 0;
  bool show_selection_window = 0;

  bool create_object_enabled = 0;
  bool create_scene_enabled = 0;

  std::vector<char*> all_available_models = {"", "monkey", "cube", "rock", "sphere"};
  std::vector<const char*> all_current_scenes;
  std::vector<std::string> active_objects_s;

  int item_objects_to_spawn = 0;
  int item_objects_to_select = 0;

  void reset_window_naming()
  {
    event_window_title = default_window_title;
    event_window_message = default_window_message;
    event_window_button = default_button_label;
    input_window_title = default_window_title;
    input_window_message = default_window_message;
    selection_window_title = default_window_title;
    selection_window_message = default_window_message;
    selection_window_button = default_button_label;
  }

  void set_show_event_window(bool flag)
  {
    show_event_window = flag;
  }

  void set_show_input_window(bool flag, SpawnTypes t)
  {
    switch (t)
    {
      case mx_object:
      {
        create_object_enabled = 1;
        break;
      }
      case mx_scene:
      {
        create_scene_enabled = 1;
        break;
      }
      case mx_null:
      default:
      {
        create_object_enabled = 0;
        create_scene_enabled = 0;
        break;
      }
    }
    show_input_window = flag;
  }

  void set_show_selection_window(bool flag)
  {
    show_selection_window = flag;
  }

  bool get_show_event_window()
  {
    return show_event_window;
  }

  bool get_show_input_window()
  {
    return show_input_window;
  }

  bool get_show_selection_window()
  {
    return show_selection_window;
  }
}