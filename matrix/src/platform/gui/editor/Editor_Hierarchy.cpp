#include "Editor_Hierarchy.h"
#include "Application.h"

namespace MX
{
  Editor_Hierarchy::Editor_Hierarchy()
    : m_root(Application::get().m_World.m_ActiveScene->m_Sg.m_Root) { }

  Editor_Hierarchy::Editor_Hierarchy(const std::string& name, ImGuiWindowFlags flags)
    : m_root(Application::get().m_World.m_ActiveScene->m_Sg.m_Root)
  {
    initialize(name, flags);
  }

  bool Editor_Hierarchy::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Hierarchy::update()
  {
    return ImGui_Window::update();
  }

  void Editor_Hierarchy::render()
  {
    if (ImGui_Window::begin())
    {
      if (ImGui::Button("Unselect"))
        Editor_Global::get_selection().clear();

      if (ImGui::BeginMenuBar())
      {
        if (ImGui::BeginMenu("New##NewObject"))
        {
          if (ImGui::MenuItem("Geometry"))
          {

          }

          if (ImGui::MenuItem("Container"))
          {

          }

          if (ImGui::BeginMenu("Light"))
          {
            if (ImGui::MenuItem("Directional Light"))
            {

            }

            if (ImGui::MenuItem("Point Light"))
            {

            }

            if (ImGui::MenuItem("Spot Light"))
            {

            }

            ImGui::EndMenu();
          }

          ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
      }

      ImGui::SetNextItemOpen(true, ImGuiCond_Once);

      // magic number (why IMGUI WHYY?!)
      ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 23.0f);
      if (traverse(Application::get().m_World.m_ActiveScene->m_Sg.m_Root, 0))
        m_break_out = false;
      ImGui::PopStyleVar();
    }

    static ImGui_ContextMenu hierarchy_context_menu("Hierarchy Context Menu");
    if (hierarchy_context_menu.begin(m_right_clicked))
    {
      if (ImGui::Button("Delete##Delete Node in Hierarchy"))
      {
        if (m_rc_node != nullptr)
        {
          m_rc_node->destroy();
          m_rc_node = nullptr;
          m_right_clicked = false;
        }
        Editor_Global::get_selection().clear();
      }

      hierarchy_context_menu.end();
    }

    ImGui_Window::end();
  }

  // traverse through all children of the given node recursively
  bool Editor_Hierarchy::traverse(const std::shared_ptr<Node> node, int counter)
  {
    static std::string prev_node;

    if (m_break_out)
      return m_break_out;

    int flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (node != nullptr)
    {
      // node has no children so it will be displayed as a leaf
      if (node->m_Children.size() == 0)
        flags |= ImGuiTreeNodeFlags_Leaf;

      std::vector<std::shared_ptr<Node>>::iterator selected;
      for (auto it = Editor_Global::get_selection().begin(); it != Editor_Global::get_selection().end(); ++it)
      {
        if (node->m_Name == (*it)->m_Name)
        {
          flags |= ImGuiTreeNodeFlags_Selected;
          
          // save the corresponding name if it needs to be deleted later
          selected = it;
          break;
        }
      }

      if (node->m_Parent != nullptr)
        ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());

      if (ImGui::TreeNodeEx(node->m_Name.c_str(), flags))
      {
        // shift is pressed for multiple selection or deselection
        if (ImGui::IsItemClicked() && ImGui::GetIO().KeyShift)
        {
          // check if node is already selected
          if (flags % 2 == 1)
          {
            // deselect by deleting its name from the current selection
            Editor_Global::get_selection().erase(selected);
          }
          else
          {
            // add to vector
            Editor_Global::get_selection().push_back(node);
          }
        }
        else if (ImGui::IsItemClicked())
        {
          Editor_Global::get_selection().clear();
          Editor_Global::get_selection().push_back(node);
        }     
        else if (ImGui::IsItemClicked(1))
        {
          m_rc_node = node;
          m_right_clicked = true;
        }

        ImGui::TreePop();

        // set up drap and drop source
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        {
          std::string send_tag = "NODE_H"; // H = Hierarchy
          ImGui::SetDragDropPayload(send_tag.c_str(), node->m_Name.c_str(), sizeof(char) * 200);
          ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget())
        {
          if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_H"))
          {
            IM_ASSERT(payload->DataSize == sizeof(char) * 200);
            std::string temp = (char*)payload->Data;

            if (node != nullptr)
            {
              std::shared_ptr<Node> new_parent = Application::get().m_World.m_ActiveScene->m_Sg.search<Node>(temp);  
              node->addChild(new_parent);
              
              m_break_out = true;              
            }
          }
          ImGui::EndDragDropTarget();
          return m_break_out;
        }

        if (!m_break_out)
        {
          for (auto it : node->m_Children)
          {
            if (m_break_out)
              return m_break_out;

            traverse(it, ++counter);

            if (m_break_out)
              return m_break_out;
          }
        }
      }

      if (node->m_Parent != nullptr)
        ImGui::Unindent();
    }

    return m_break_out;
  }
}