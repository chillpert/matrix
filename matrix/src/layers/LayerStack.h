#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "matrix/src/layers/Layer.h"
#include <vector>

namespace MX
{
  class LayerStack
  {
  public:
    MX_API LayerStack() {}
    MX_API ~LayerStack() = default;

    MX_API void push(Layer* layer);
    MX_API void pop(Layer* layer);

    MX_API std::string toString();
    MX_API size_t getSize() { return m_Layers.size(); }
  private:
    std::vector<Layer*> m_Layers;
  };
}

#endif // LAYERSTACK_H