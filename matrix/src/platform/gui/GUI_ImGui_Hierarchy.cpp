#include <GUI_ImGui.h>
#include <Application.h>
#include <World.h>

namespace MX
{
  static bool draw_scene_graph = 1;

  static void draw_scene_graph_menu(Node &it);
  static void draw_outline_menu();

  void renderHierarchyWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 0;
    static bool no_move = 0;
    static bool no_resize = 0;
    static bool no_collapse = 1;
    static bool no_nav = 0;
    static bool no_background = 0;
    static bool no_bring_to_front = 0;

    static ImGuiWindowFlags window_flags = 0;

    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    if (ImGui::Begin("Hierarchy", &p_open_hierarchy, window_flags))
    {
      if (!p_open_hierarchy)
        hierarchy_window_enabled = 0;

      if (ImGui::BeginMenuBar())
      {
        if (ImGui::MenuItem("Scene Graph", "", true, !draw_scene_graph))
          draw_scene_graph = 1;

        if (ImGui::MenuItem("Outline", "", true, draw_scene_graph))
          draw_scene_graph = 0;
        
        ImGui::EndMenuBar();
      }

      if (draw_scene_graph)
        draw_scene_graph_menu(*MX_WORLD.m_ActiveScene->m_Sg.m_Root);
      else  
        draw_outline_menu();
    }
    ImGui::End();
  #endif
  }

  static void draw_scene_graph_menu(Node &it)
  {
  #ifdef MX_IMGUI_ACTIVE
    if (it.m_Name != "Root")
      ImGui::Indent(20.0f);

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    
    if (ImGui::TreeNode(it.m_Name.c_str()))
    {
      ImGui::TreePop();
      
      if (!it.m_Children.empty())
      {
        for (auto itChild : it.m_Children)
          draw_scene_graph_menu(*itChild);
      }
    }

    if (it.m_Name != "Root")
      ImGui::Unindent();
  #endif
  }

  static void draw_outline_menu()
  {
  #ifdef MX_IMGUI_ACTIVE
    static size_t selected = -1;
    static size_t prev_selcted = selected;

    std::shared_ptr<Node> temp;

    for (size_t n = 0; n < all_objects.size(); n++)
    {
      temp = current_scenegraph->search(std::string(all_objects.at(n)), current_root);
      if (ImGui::Selectable(temp->m_Name.c_str(), selected == n))
        selected = n;
    }

    if (selected >= 0 && selected < all_objects.size() && temp != nullptr && prev_selcted != selected)
    {
      prev_selcted = selected;
      needs_refresh = 1;
      current_node = current_scenegraph->search(std::string(all_objects.at(selected)), current_root);;
    }

  #endif
  }
}