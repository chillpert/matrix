#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "Layer.h"

namespace MX
{
  class ImGui_Layer : public Layer
  {
  public:
    ImGui_Layer();

    void OnAttach();
    void OnDetach();

    void OnUpdate();
    void OnEvent(Event& event);
  
  private:
    float m_time = 0.0f;
  };
}

#endif // IMGUI_LAYER_H