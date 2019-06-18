#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"
#include "matrix/src/layers/World.h"

namespace MX
{
  std::shared_ptr<Node> current_node;
  std::shared_ptr<Scene> current_scene;
  SceneGraph *current_scenegraph;
  std::shared_ptr<Node> current_root;
  std::vector<std::shared_ptr<Scene>> *all_scenes;
  
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

  std::vector<const char*> all_models;
  std::vector<const char*> all_shaders;
  std::vector<const char*> all_diffuse_maps;
  std::vector<const char*> all_normal_maps;
  std::vector<const char*> all_bump_maps;

  std::vector<const char*> all_current_scenes;
  std::vector<const char*> all_objects;
}