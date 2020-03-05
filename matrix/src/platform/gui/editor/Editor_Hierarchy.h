#ifndef EDITOR_HIERARCHY_H
#define EDITOR_HIERARCHY_H

#include "GUI_ImGui_Window.h"
#include "Editor_Global.h"

namespace MX
{
  class Editor_Hierarchy : public ImGui_Window, public Editor_Global
  {
  public:
    MX_API Editor_Hierarchy();
    MX_API Editor_Hierarchy(const char* name, ImGuiWindowFlags flags = 0);

    MX_API bool initialize(const char* name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override; 
  
  private:
    MX_API bool traverse(const std::shared_ptr<Node> node, int counter);

    std::shared_ptr<Node> m_root;
    bool m_break_out = false;
    bool m_right_clicked = false;
    std::shared_ptr<Node> m_rc_node = nullptr;
  };
}

#endif // EDITOR_HIERARCHY_H