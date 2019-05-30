#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"

namespace MX
{
  InputTypes currentInputType = mx_name;

  std::string event_window_title = "undefined window title";
  std::string event_window_message = "undefined window message";
  std::string event_window_button = "undefined window button label";

  std::string input_window_title = "undefined window title";
  std::string input_window_message = "undefined window message";

  bool show_event_window = 0;
  bool show_input_window = 0;

  std::vector<char*> all_available_models = {"", "monkey", "cube", "rock", "sphere"};
  std::vector<std::string> active_objects_s;

  int item_objects_to_spawn = 0;
  int item_objects_to_select = 0;

  void set_show_event_window(bool flag)
  {
    show_event_window = flag;
  }

  void set_show_input_window(bool flag)
  {
    show_input_window = flag;
  }

  bool get_show_event_window()
  {
    return show_event_window;
  }

  bool get_show_input_window()
  {
    return show_input_window;
  }
}