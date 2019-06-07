#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/layers/World.h"

namespace MX
{
  static bool no_titlebar = 0;
  static bool no_scrollbar = 0;
  static bool no_menu = 0;
  static bool no_move = 1;
  static bool no_resize = 1;
  static bool no_collapse = 1;
  static bool no_close = 0;
  static bool no_nav = 0;
  static bool no_background = 0;
  static bool no_bring_to_front = 0;

  static bool draw_scene_graph = 1;

  void drawSceneGraph(Node &it);

  void GUI_ImGui::renderHierarchyWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
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

    ImGui::Begin("Hierarchy", &p_open_hierarchy, window_flags);

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
      drawSceneGraph(*World::get().m_ActiveScene->m_Sg.m_Root);  

    if (editor_window_enabled)
    {
      ImGui::SetWindowPos(ImVec2(0.0f, float (Application::get().m_Window->m_Props.m_Height) / 2.0f + 21.0f));
      ImGui::SetWindowSize(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 5.0f, float (Application::get().m_Window->m_Props.m_Height)));
    }
    else
    {
      ImGui::SetWindowPos(ImVec2(0.0f, 20.0f));
      ImGui::SetWindowSize(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 5.0f, float (Application::get().m_Window->m_Props.m_Height)));
    }
     
    ImGui::End();
  #endif
  }

  void drawSceneGraph(Node &it)
  {
  #ifdef MX_IMGUI_ACTIVE
    if (ImGui::TreeNode(it.m_Name.c_str()))
    {

      ImGui::TreePop();
    
      if (!it.getChildren().empty())
      {
        for (Node *itChild : it.getChildren())
          drawSceneGraph(*itChild);
      }
    }
  #endif
  }
}