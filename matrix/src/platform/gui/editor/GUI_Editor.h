#ifndef GUI_EDITOR
#define GUI_EDITOR

#include "GUI_ImGui.h"
#include <GUI_ImGui_Flags.h>

namespace MX
{
  class GUI_Editor : public GUI_ImGui
  {
  public:
    MX_API GUI_Editor() = default;

    MX_API void initialize() override;
    MX_API void update() override;
    MX_API void render() override;
    MX_API void clean() override;
    MX_API void clear() override;

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
  };
}

#endif // GUI_EDITOR