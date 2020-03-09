#ifndef WINDOW_LAYER_H
#define WINDOW_LAYER_H

#include "Layer.h"

namespace MX
{
  class Window_Layer : public Layer
  {
  public:
    MX_API Window_Layer(const std::string& name);

    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onRender() override;
    void onEvent(Event& event) override;
  };
}

#endif // WINDOW_LAYER_H