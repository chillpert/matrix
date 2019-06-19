#ifndef GUI_IMGUI_FLAGS_H
#define GUI_IMGUI_FLAGS_H

#include <stdafx.h>
#include <Scene.h>

#include <imgui.h>

namespace MX
{
  MX_API extern std::shared_ptr<Node> current_node;
  MX_API extern std::shared_ptr<Scene> current_scene;
  MX_API extern SceneGraph *current_scenegraph;
  MX_API extern std::shared_ptr<Node> current_root;
  MX_API extern std::vector<std::shared_ptr<Scene>> *all_scenes;

  MX_API extern std::vector<const char*> all_models;
  MX_API extern std::vector<const char*> all_shaders;
  MX_API extern std::vector<const char*> all_diffuse_maps;
  MX_API extern std::vector<const char*> all_normal_maps;
  MX_API extern std::vector<const char*> all_bump_maps;

  MX_API extern std::vector<const char*> all_current_scenes;
  MX_API extern std::vector<const char*> all_objects;

  MX_API extern bool needs_refresh;

  MX_API extern float file_inspector_width;
  MX_API extern float file_inspector_height;
  MX_API extern std::string file_inspector_name;

  #ifdef MX_OPENGL_ACTIVE
    MX_API extern void* file_inspector_id;
  #elif MX_DIRECTX_ACTIVE
    MX_API extern u_int64_t *file_inspector_id;
  #endif

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
  MX_API extern bool file_inspector_enabled;
}

#endif // GUI_IMGUI_FLAGS_H