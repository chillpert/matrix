#ifndef GUI_IMGUI_H
#define GUI_IMGUI_H

#include "matrix/src/platform/gui/GUI.h"

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
  void renderEditor();

  class GUI_ImGui: public GUI
  {
  public: 
    MX_API GUI_ImGui() {}
    MX_API ~GUI_ImGui() {}

    MX_API void initialize() override;
    MX_API void update() override;
    MX_API void render() override;
    MX_API void clean() override;
  };
}

#endif // GUI_IMGUI_H