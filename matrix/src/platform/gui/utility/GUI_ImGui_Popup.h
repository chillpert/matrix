#ifndef GUI_IMGUI_POPUP_H
#define GUI_IMGUI_POPUP_H

#include "GUI_ImGui_Window.h"

namespace MX
{
  class ImGui_Popup : public ImGui_Window
  {
  public:
    MX_API ImGui_Popup() = default;
    MX_API ImGui_Popup(const char* name, ImGuiWindowFlags flags = 0);

    MX_API virtual void open();
    MX_API virtual void close();
    
    MX_API virtual bool begin() override;
    MX_API virtual bool beginModal();
    
    MX_API virtual void end() override;
  };

  class ImGui_PopupHoverInfo : private ImGui_Popup
  {
  public:
    MX_API ImGui_PopupHoverInfo();
    MX_API ImGui_PopupHoverInfo(const char* name, ImGuiWindowFlags flags = 0);

    MX_API void render(const char* message, bool condition);

    float m_condition_length;

  private:    
    bool m_show_hover_info;
    bool m_initial_condition;
    float m_time_on_condition;
  };
}

#endif // GUI_IMGUI_POPUP_H