#ifndef GUI_IMGUI_H
#define GUI_IMGUI_H

#include <GUI.h>
#include <GUI_ImGui_Flags.h>

#include <imgui.h>
#include <World.h>
#include <Scene.h>

namespace MX
{
  class GUI_ImGui : public GUI
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
    MX_API void clear() override;
  };

  // GUI_ImGui_Editor.cpp
  void renderFileInspectorWindow();
  void renderScenesMenu();
  void renderAssestsMenu();
  void renderTransformMenu();
  void renderSpawnMenu();
  void renderViewportSettingsMenu();

  // GUI_ImGui_Hierarchy.cpp
  void renderOutline();
  void renderSceneGraph();
  // GUI_ImGui_MenuBar.cpp
  void renderMenuBar();

  // GUI_ImGui_Viewport.cpp
  void renderViewport();
  void renderDockSpace();
  void renderPerformanceMonitor();

  // GUI_ImGui_Logger.cpp
  void renderLoggerWindow();
}

#endif // GUI_IMGUI_H