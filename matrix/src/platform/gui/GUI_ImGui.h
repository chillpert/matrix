#ifndef GUI_IMGUI_H
#define GUI_IMGUI_H

#include "matrix/src/platform/gui/GUI.h"
#include "matrix/src/platform/gui/GUI_ImGui_Flags.h"

#include <IMGUI/imgui.h>
#include "matrix/src/layers/World.h"
#include "matrix/src/layers/Scene.h"
#include "matrix/src/platform/api/Model.h"
#ifdef MX_OPENGL_ACTIVE 
  #include "matrix/src/platform/api/Model_OpenGL.h"
#elif MX_DIRECTX_ACTIVE
  #include "matrix/src/platform/api/Model_DirectX.h"
#endif

namespace MX
{
  class GUI_ImGui: public GUI
  {
  public: 
    MX_API GUI_ImGui() {}
    MX_API ~GUI_ImGui() {}

    MX_API void initialize() override;
    MX_API void update() override;
    MX_API void render() override;
    MX_API void clean() override;
  
  private:
    // GUI_ImGui_Events.cpp
    MX_API static void renderInputWindow();
    MX_API static void renderEventWindow();

    // GUI_ImGui_Editor.cpp
    MX_API static void renderEditorWindow();

    // GUI_ImGui_Hierarchy.cpp
    MX_API static void renderHierarchyWindow();

    // GUI_ImGui_MenuBar.cpp
    MX_API static void renderMenuBar();


  };
}

#endif // GUI_IMGUI_H