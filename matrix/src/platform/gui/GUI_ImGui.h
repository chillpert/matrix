#ifndef GUI_IMGUI_H
#define GUI_IMGUI_H

#include <GUI.h>
#include <GUI_ImGui_Flags.h>

#include <imgui.h>
#include <World.h>
#include <Scene.h>
#include <Model.h>
#include <Model_OpenGL.h>

namespace MX
{
  class GUI_ImGui: public GUI
  {
  public: 
    MX_API GUI_ImGui() = default;
    MX_API ~GUI_ImGui() = default;

    MX_API GUI_ImGui(const GUI_ImGui&) = default;
    MX_API GUI_ImGui &operator=(const GUI_ImGui&) = default;

    MX_API void initialize() override;
    MX_API void update() override;
    MX_API void render() override;
    MX_API void clean() override;
  };

  // GUI_ImGui_Editor.cpp
  MX_API void renderEditorWindow();
  MX_API void renderFileInspectorWindow();

  // GUI_ImGui_Hierarchy.cpp
  MX_API void renderHierarchyWindow();

  // GUI_ImGui_MenuBar.cpp
  MX_API void renderMenuBar();

  // GUI_ImGui.cpp
  MX_API void renderViewport();
  MX_API void renderDockSpace();

  // GUI_ImGui_Logger.cpp
  MX_API void renderLoggerWindow();
}

#endif // GUI_IMGUI_H