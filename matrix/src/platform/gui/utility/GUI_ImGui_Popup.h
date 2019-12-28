#ifndef GUI_IMGUI_POPUP_H
#define GUI_IMGUI_POPUP_H

#include "GUI_ImGui_Window.h"

namespace MX
{
  class ImGui_Popup : public ImGui_Window
  {
  public:
    MX_API ImGui_Popup() = default;

    MX_API void open();
    MX_API bool begin() override;
    MX_API void end() override;
  };
}

#endif // GUI_IMGUI_POPUP_H