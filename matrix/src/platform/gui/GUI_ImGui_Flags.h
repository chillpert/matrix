#ifndef GUI_IMGUI_FLAGS_H
#define GUI_IMGUI_FLAGS_H

#include "matrix/src/pch/stdafx.h"

#include <imgui.h>

namespace MX
{
  // font
  MX_API extern ImFont* font_global;

  // all object files in model directory
  MX_API extern std::vector<const char*> all_available_models;
  // all texture files in texture directory
  MX_API extern std::vector<const char*> all_available_textures;
  // all shaders files in shader directory
  MX_API extern std::vector<const char*> all_available_shaders;

  // all existing scenes
  MX_API extern std::vector<const char*> all_current_scenes;
  // all existing objects in scene
  MX_API extern std::vector<const char*> all_current_objects;

  // imgui combo flags
  MX_API extern int item_objects_to_spawn;

  MX_API extern int item_objects_to_select;
  MX_API extern int item_shaders_to_select;
  MX_API extern int item_texture_to_select;

  // all mx-logger messages are being stored in here
  MX_API extern std::vector<std::pair<std::string, ImVec4>> logger_messages_for_gui;

  // flags for handling close window events
  MX_API extern bool p_open_editor;
  MX_API extern bool p_open_hierarchy;
  MX_API extern bool p_open_logger;
  MX_API extern bool p_open_viewport;
  MX_API extern bool p_open_demo;

  // flags for toggling window visibility
  MX_API extern bool viewport_enabled;
  MX_API extern bool menubar_enabled;
  MX_API extern bool editor_window_enabled;
  MX_API extern bool hierarchy_window_enabled;
  MX_API extern bool logger_window_enabled;
  MX_API extern bool demo_window_enabled;
}

#endif // GUI_IMGUI_FLAGS_H