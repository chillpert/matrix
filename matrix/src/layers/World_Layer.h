#ifndef WORLD_LAYER_H
#define WORLD_LAYER_H

#include "Layer.h"

namespace MX
{
  class World_Layer : public Layer
  {
  public:
    MX_API World_Layer(const std::string& name);

    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onRender() override;
    void onEvent(Event& event) override;
  };
}

#endif // WORLD_LAYER_H