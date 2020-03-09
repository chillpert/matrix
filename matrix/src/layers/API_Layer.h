#ifndef API_LAYER_H
#define API_LAYER_H

#include "Layer.h"

namespace MX
{
  class API_Layer : public Layer
  {
  public:
    MX_API API_Layer(const std::string& name);

    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onRender() override;
    void onEvent(Event& event) override;
  };
}

#endif // API_LAYER_H