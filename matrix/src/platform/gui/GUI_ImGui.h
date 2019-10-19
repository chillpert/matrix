#ifndef GUI_IMGUI_H
#define GUI_IMGUI_H

#include <GUI.h>

#include <imgui.h>
#include <World.h>
#include <Scene.h>

namespace MX
{
  class GUI_ImGui : public GUI
  {
  public: 
    MX_API GUI_ImGui() = default;
    MX_API virtual ~GUI_ImGui() = default;

    MX_API GUI_ImGui(const GUI_ImGui&) = default;
    MX_API virtual GUI_ImGui &operator=(const GUI_ImGui&) = default;

    MX_API virtual void initialize() override;
    MX_API virtual void update() override;
    MX_API virtual void render() override;
    MX_API virtual void clean() override;
    MX_API virtual void clear() override;
  };
}

#endif // GUI_IMGUI_H