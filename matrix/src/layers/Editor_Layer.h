#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include "Layer.h"

namespace MX
{
  class Editor_Layer : public Layer
  {
  public:
    Editor_Layer(const std::string& name);

    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onRender() override;
    void onEvent(Event& event) override;
  }; 
}

#endif // EDITOR_LAYER_H