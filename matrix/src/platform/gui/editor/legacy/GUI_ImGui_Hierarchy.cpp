#include "GUI_Editor.h"
#include "Application.h"
#include "World.h"

namespace MX
{
  static void draw_scene_graph_menu(Node &it);

  void GUI_Editor::renderSceneGraph()
  {
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
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

    if (ImGui::Begin("Scene Graph", &p_open_scenegraph, window_flags))
      draw_scene_graph_menu(*MX_WORLD.m_ActiveScene->m_Sg.m_Root);
    
    ImGui::End();
  }

  void GUI_Editor::renderOutline()
  {
  #ifdef MX_IMGUI_ACTIVE
    static bool no_titlebar = 0;
    static bool no_scrollbar = 0;
    static bool no_menu = 1;
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

    if (ImGui::Begin("Outline", &p_open_outline, window_flags))
    {
      static size_t selected = -1;
      static size_t prev_selected = selected;

      std::shared_ptr<Node> temp = nullptr;

      ImGui::Columns(3, "outline window", true);
      for (size_t n = 0; n < all_objects.size(); n++)
      {
        temp = current_scenegraph->search<Node>(std::string(all_objects.at(n)));
        if (ImGui::Selectable(temp->m_Name.c_str(), selected == n))
          selected = n;
        
        ImGui::NextColumn();

        std::string button_label = "V##" + std::to_string(n);
        if (temp->m_visible)
        {
           if (ImGui::Button(button_label.c_str()))
            temp->m_visible = 0;
        }
        else
        {
          ImGui::PushID(n);
          ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
          ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
          ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

          if (ImGui::Button(button_label.c_str()))
            temp->m_visible = 1;
          
          ImGui::PopStyleColor(3);
          ImGui::PopID();
        }

        ImGui::NextColumn();

        ImGui::Text(temp->getIdentifier().c_str());
      
        ImGui::NextColumn();
      }
      ImGui::Columns(1);

      if (selected >= 0 && selected < all_objects.size() && temp != nullptr && prev_selected != selected && cool_down == 0)
      {
        prev_selected = selected;
        needs_refresh = 1;
        cool_down = 1;

        current_node = current_scenegraph->search<Node>(std::string(all_objects.at(selected)));
        MX_SUCCESS("MX: GUI: ImGui: Changing current node");
      }
    }
    ImGui::End();
  #endif
  }

  static void draw_scene_graph_menu(Node &it)
  {
  #ifdef MX_IMGUI_ACTIVE
    if (it.m_Name != default_root_name)
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

    if (it.m_Name != default_root_name)
      ImGui::Unindent();
  #endif
  }
}