#ifndef EDITOR_HIERARCHY_H
#define EDITOR_HIERARCHY_H

#include "GUI_ImGui_Window.h"
#include "Editor_Global.h"

namespace MX
{
  class Editor_Hierachy : public ImGui_Window, public Editor_Global
  {
  public:
    MX_API Editor_Hierachy();
    MX_API Editor_Hierachy(const std::string& name, ImGuiWindowFlags flags = 0);

    MX_API bool initialize(const std::string& name, ImGuiWindowFlags flags = 0) override;
    MX_API bool update() override;
    MX_API void render() override; 
  
  private:
    MX_API void traverse(const std::shared_ptr<Node> node, int counter);

    std::shared_ptr<Node> m_root;    
  };
}

#endif // EDITOR_HIERARCHY_H