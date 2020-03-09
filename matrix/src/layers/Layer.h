#ifndef LAYER_H
#define LAYER_H

#include "stdafx.h"
#include "Event.h"

namespace MX
{
  class Layer
  {
  public:
    MX_API Layer(const std::string& name = "Layer");
    MX_API virtual ~Layer();

    MX_API virtual void onAttach() {}
    MX_API virtual void onDetach() {}
    MX_API virtual void onUpdate() {}
    MX_API virtual void onRender() {}
    MX_API virtual void onEvent(Event& event) {}

    std::string m_name;
  };
}

#endif // LAYER_H