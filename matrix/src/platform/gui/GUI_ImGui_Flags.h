#ifndef GUI_IMGUI_FLAGS_H
#define GUI_IMGUI_FLAGS_H

#include "matrix/src/pch/stdafx.h"

namespace MX
{
  enum InputTypes
  {
    mx_name,      // string input
    mx_resolution // two integer input
  };

  //const char* all_available_models[] = {"", "monkey", "cube", "rock", "sphere"};

  MX_API extern std::vector<char*> all_available_models;

  MX_API extern int item_objects_to_spawn;
  MX_API extern int item_objects_to_select;

  MX_API extern std::vector<std::string> active_objects_s;

  MX_API extern InputTypes currentInputType;

  MX_API extern std::string event_window_title;
  MX_API extern std::string event_window_message;
  MX_API extern std::string event_window_button;

  MX_API extern std::string input_window_title;
  MX_API extern std::string input_window_message;

  const float middle_offset_x = 250.0f;
  const float middle_offset_y = 100.0f;

  MX_API void set_show_event_window(bool flag);
  MX_API void set_show_input_window(bool flag);

  MX_API bool get_show_event_window();
  MX_API bool get_show_input_window();
}

#endif // GUI_IMGUI_FLAGS_H