#include "matrix/src/platform/gui/GUI_ImGui.h"
#include "matrix/src/Application.h"
#include "matrix/src/layers/World.h"

namespace MX
{
  static bool draw_scene_graph = 1;

  static void draw_scene_graph_menu(Node &it);
  static void draw_outline_menu();

  void GUI_ImGui::renderHierarchyWindow()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 0;
    static bool no_move = 1;
    static bool no_resize = 1;
    static bool no_collapse = 1;
    // static bool no_close = 0;
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
      draw_scene_graph_menu(*World::get().m_ActiveScene->m_Sg.m_Root);
    else  
      draw_outline_menu();

    if (editor_window_enabled)
    {
      ImGui::SetWindowPos(ImVec2(0.0f, float (Application::get().m_Window->m_Props.m_Height) / 2.0f + 19.0f));
      ImGui::SetWindowSize(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 5.0f, float (Application::get().m_Window->m_Props.m_Height)));
    }
    else
    {
      ImGui::SetWindowPos(ImVec2(0.0f, 19.0f));
      ImGui::SetWindowSize(ImVec2(float (Application::get().m_Window->m_Props.m_Width) / 5.0f, float (Application::get().m_Window->m_Props.m_Height)));
    }
     
    ImGui::End();
  #endif
  }

  static void draw_scene_graph_menu(Node &it)
  {
  #ifdef MX_IMGUI_ACTIVE
    if (it.m_Name != "root")
      ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
    
    if (ImGui::TreeNode(it.m_Name.c_str()))
    {
      ImGui::TreePop();
      

      if (!it.getChildren().empty())
      {
        for (Node *itChild : it.getChildren())
          draw_scene_graph_menu(*itChild);
      }
    }

    if (it.m_Name != "root")
      ImGui::Unindent();
  #endif
  }

  static void draw_outline_menu()
  {
  #ifdef MX_IMGUI_ACTIVE
    for (auto it : all_current_objects)
    {
      const std::string node_name = std::string(it);

      if (node_name != "root")
      {
        if (ImGui::TreeNode((node_name + "##outline tree").c_str()))
        {
          try
          {
            Node *temp = MX::World::get().m_ActiveScene->m_Sg.search(std::string(it), MX::World::get().m_ActiveScene->m_Sg.m_Root);
            ImGui::Text(("Shader: " + temp->m_Shader->getName()).c_str());
            ImGui::Text(("Texture: " + temp->m_Texture->getName()).c_str());
            ImGui::Text(("Model: " + temp->m_Model->getName()).c_str());
          }
          catch (const std::exception &e) { }

          ImGui::TreePop();
        }
      }
    }
  #endif
  }
}