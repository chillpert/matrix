#ifndef GUI_IMGUI_FLAGS_H
#define GUI_IMGUI_FLAGS_H

#include <stdafx.h>
#include <Scene.h>

#include <imgui.h>

namespace MX
{
  extern bool global_cool_down;
  extern bool cool_down;

  extern std::shared_ptr<Node> current_node;
  extern std::shared_ptr<Scene> current_scene;
  extern SceneGraph *current_scenegraph;
  extern std::shared_ptr<Node> current_root;
  extern std::vector<std::shared_ptr<Scene>> *all_scenes;

  extern std::vector<std::map<int, std::shared_ptr<Model>>> model_test;

  extern std::vector<const char*> all_models;
  extern std::vector<const char*> all_shaders;
  extern std::vector<const char*> all_diffuse_maps;
  extern std::vector<const char*> all_normal_maps;
  extern std::vector<const char*> all_bump_maps;
  extern std::vector<const char*> all_height_maps;

  extern std::vector<const char*> all_current_scenes;
  extern std::vector<const char*> all_objects;

  extern bool needs_refresh;

  extern float file_inspector_width;
  extern float file_inspector_height;
  extern std::string file_inspector_name;

  #ifdef MX_OPENGL_ACTIVE
    extern void* file_inspector_id;
  #elif MX_DIRECTX_ACTIVE
    extern u_int64_t *file_inspector_id;
  #endif

  // all mx-logger messages are being stored in here
  extern std::vector<std::pair<std::string, ImVec4>> logger_messages_for_gui;

  // flags for handling close window events
  extern bool p_open_spawn;
  extern bool p_open_scenegraph;
  extern bool p_open_outline;
  extern bool p_open_scenes;
  extern bool p_open_assets;
  extern bool p_open_transform;
  extern bool p_open_hierarchy;
  extern bool p_open_logger;
  extern bool p_open_demo;
  extern bool p_open_performance_monitor;
  extern bool p_open_viewport;

  // flags for toggling window visibility
  extern bool spawn_window_enabled;
  extern bool scenegraph_enabled;
  extern bool outline_enabled;
  extern bool menubar_enabled;
  extern bool hierarchy_window_enabled;
  extern bool scenes_window_enabled;
  extern bool assets_window_enabled;
  extern bool transform_window_enabled;
  extern bool logger_window_enabled;
  extern bool demo_window_enabled;
  extern bool file_inspector_enabled;
  extern bool performance_monitor_enabled;
  const bool viewport_enabled = 1;
}

#endif // GUI_IMGUI_FLAGS_H