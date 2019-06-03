#ifndef GUI_IMGUI_FLAGS_H
#define GUI_IMGUI_FLAGS_H

#include "matrix/src/pch/stdafx.h"

#include <IMGUI/imgui.h>

namespace MX
{
  // needs to be set before calling an input event window
  enum InputTypes
  {
    mx_name,      // string input
    mx_resolution // two integer input
  };

  // global flag for input type
  MX_API extern InputTypes currentInputType;

  // needs to be set before calling a selection event window
  enum SelectionTypes
  {
    mx_scene,     // create scene
    mx_object,    // create object
    mx_null       // create nothing
  };

  // global flag for selection type
  MX_API extern SelectionTypes currentSelectionType;

  // all object files in model directory
  MX_API extern std::vector<char*> all_available_models;

  // all scenes available
  MX_API extern std::vector<const char*> all_current_scenes;

  // all shaders files in directory
  MX_API extern std::vector<const char*> all_available_shaders;

  // all already spawned objects
  MX_API extern std::vector<std::string> active_objects_s;

  // imgui combo flags
  MX_API extern int item_objects_to_spawn;
  MX_API extern int item_objects_to_select;
  MX_API extern int item_shaders_to_select;

  // event window naming
  MX_API extern std::string event_window_title;
  MX_API extern std::string event_window_message;
  MX_API extern std::string event_window_button;

  // all mx-logger messages are being stored in here
  MX_API extern std::vector<std::pair<std::string, ImVec4>> logger_messages_for_gui;

  // flags for handling close window events
  MX_API extern bool p_open_editor;
  MX_API extern bool p_open_hierarchy;
  MX_API extern bool p_open_logger;
  MX_API extern bool p_open_event;

  // flags for toggling window visibility
  MX_API extern bool event_window_enabled;
  MX_API extern bool input_window_enabled;
  MX_API extern bool selection_window_enabled;
  MX_API extern bool menubar_enabled;
  MX_API extern bool editor_window_enabled;
  MX_API extern bool hierarchy_window_enabled;
  MX_API extern bool logger_window_enabled;

  // resets title, message and buttons of all windows
  MX_API void reset_window_naming();

  // checks for all available object files
  MX_API void check_folder_for_objects();
  MX_API void check_folder_for_shaders();

  // for centering event windows in the middle of the screen
  const float middle_offset_x = 250.0f;
  const float middle_offset_y = 100.0f;
}

#endif // GUI_IMGUI_FLAGS_H