#include "Editor_Hierarchy.h"
#include "Application.h"

namespace MX
{
  Editor_Hierarchy::Editor_Hierarchy()
  {
    if (MX_SCENE != nullptr)
      m_root = MX_ROOT;
    else
      m_root = nullptr;
  }

  Editor_Hierarchy::Editor_Hierarchy(const char* name, ImGuiWindowFlags flags)
  {
    if (MX_SCENE != nullptr)
      m_root = MX_ROOT;
    else
      m_root = nullptr;

    initialize(name, flags);
  }

  bool Editor_Hierarchy::initialize(const char* name, ImGuiWindowFlags flags)
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
            std::shared_ptr<GeometryNode> node = std::make_shared<GeometryNode>("Object");
            if (MX_SCENE != nullptr)
              MX_SCENEGRAPH.push(node);
          }

          if (ImGui::MenuItem("Container"))
          {
            std::shared_ptr<ContainerNode> node = std::make_shared<ContainerNode>("Container");
            if (MX_SCENE != nullptr)
              MX_SCENEGRAPH.push(node);
          }

          if (ImGui::BeginMenu("Light"))
          {
            if (ImGui::MenuItem("Directional Light"))
            {
              std::shared_ptr<DirectionalLightNode> node = std::make_shared<DirectionalLightNode>("DirectionalLight");
              if (MX_SCENE != nullptr)
                MX_SCENEGRAPH.push(node);
            }

            if (ImGui::MenuItem("Point Light"))
            {
              std::shared_ptr<PointLightNode> node = std::make_shared<PointLightNode>("PointLight");
              if (MX_SCENE != nullptr)
                MX_SCENEGRAPH.push(node);
            }

            if (ImGui::MenuItem("Spot Light"))
            {
              std::shared_ptr<SpotLightNode> node = std::make_shared<SpotLightNode>("SpotLight");
              if (MX_SCENE != nullptr)
                MX_SCENEGRAPH.push(node);
            }

            ImGui::EndMenu();
          }

          ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
      }

      ImGui::SetNextItemOpen(true, ImGuiCond_Once);

      if (MX_SCENE != nullptr)
      {
        // magic number (why IMGUI WHYY?!)
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10.0f);
        if (traverse(MX_ROOT, 0))
          m_break_out = false;
        ImGui::PopStyleVar();
      }
    }

    static ImGui_Popup hierarchy_context_menu("Hierachy Context Menu");
    if (m_right_clicked)
    {
      m_right_clicked = false;
      hierarchy_context_menu.open();
    }

    if (hierarchy_context_menu.begin())
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

        hierarchy_context_menu.close();
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
        ImGui::Indent(10.0f);//ImGui::GetTreeNodeToLabelSpacing());

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
        else if (ImGui::IsItemActive() && ImGui::IsMouseDoubleClicked(0))
        {
          Editor_Global::get_selection().clear();
          Editor_Global::get_selection().push_back(node);
        }
        else if (ImGui::IsItemClicked(1))
        {
          m_rc_node = node;
          m_right_clicked = true;
        }

        // set up drap and drop source
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        {
          std::string send_tag = "NODE_H"; // H = Hierarchy
          ImGui::SetDragDropPayload(send_tag.c_str(), node->m_Name.c_str(), sizeof(char) * 200);
          ImGui::EndDragDropSource();
        }
        
        ImGui::TreePop();

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

      if (ImGui::BeginDragDropTarget())
      {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_H"))
        {
          IM_ASSERT(payload->DataSize == sizeof(char) * 200);
          std::string temp = (char*)payload->Data;

          if (node != nullptr)
          {
            if (temp != Constants::default_root_name)
            {
              if (MX_SCENE != nullptr)
              {
                std::shared_ptr<Node> new_parent = MX_SCENEGRAPH.search<Node>(temp);  
                node->addChild(new_parent);
              }
            }

            m_break_out = true;              
          }
        }
        ImGui::EndDragDropTarget();
        return m_break_out;
      }

      if (node->m_Parent != nullptr)
        ImGui::Unindent();
    }

    return m_break_out;
  }
}