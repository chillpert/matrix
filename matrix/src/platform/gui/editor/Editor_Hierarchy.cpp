#include "Editor_Hierarchy.h"
#include "Application.h"

namespace MX
{
  Editor_Hierachy::Editor_Hierachy()
    : m_root(Application::get().m_World.m_ActiveScene->m_Sg.m_Root) { }

  Editor_Hierachy::Editor_Hierachy(const std::string& name, ImGuiWindowFlags flags)
    : m_root(Application::get().m_World.m_ActiveScene->m_Sg.m_Root)
  {
    initialize(name, flags);
  }

  bool Editor_Hierachy::initialize(const std::string& name, ImGuiWindowFlags flags)
  {
    return ImGui_Window::initialize(name, flags);
  }

  bool Editor_Hierachy::update()
  {
    return ImGui_Window::update();
  }

  void Editor_Hierachy::render()
  {
    if (ImGui_Window::begin())
    {
      ImGui::SetNextItemOpen(true, ImGuiCond_Once);
      traverse(m_root, 0);
    }

    ImGui_Window::end();
  }

  // traverse through all children of the given node recursively
  void Editor_Hierachy::traverse(const std::shared_ptr<Node> node, int counter)
  {
    int flags = ImGuiTreeNodeFlags_OpenOnArrow;

    if (node != nullptr)
    {
      // node has no children so it will be displayed as a leaf
      if (node->m_Children.size() == 0)
        flags |= ImGuiTreeNodeFlags_Leaf;

      std::vector<std::shared_ptr<Node>>::iterator selected;
      for (auto it = get_selection().begin(); it != get_selection().end(); ++it)
      {
        if (node->m_Name == (*it)->m_Name)
        {
          flags |= ImGuiTreeNodeFlags_Selected;
          
          // save the corresponding name if it needs to be deleted later
          selected = it;
          break;
        }
      }

      if (ImGui::TreeNodeEx(node->m_Name.c_str(), flags))
      {
        // shift is pressed for multiple selection or deselection
        if (ImGui::IsItemClicked() && ImGui::GetIO().KeyShift)
        {
          // check if node is already selected
          if (flags % 2 == 1)
          {
            // deselect by deleting its name from the current selection
            get_selection().erase(selected);
          }
          else
          {
            // add to vector
            get_selection().push_back(node);
          }
        }
        else if (ImGui::IsItemClicked())
        {
          get_selection().clear();
          get_selection().push_back(node);
        }

        ImGui::TreePop();

        for (auto it : node->m_Children)
          traverse(it, ++counter);
      }
    }
  }
}