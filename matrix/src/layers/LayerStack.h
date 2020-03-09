#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "Layer.h"

namespace MX
{
  class LayerStack
  {
  public:
    MX_API LayerStack();
    MX_API ~LayerStack();

    MX_API void pushLayer(Layer* layer);
    MX_API void pushOverlay(Layer* overlay);
    MX_API void popLayer(Layer* layer);
    MX_API void popOverlay(Layer* overlay);

    MX_API std::string toString();
    MX_API size_t size() { return m_Layers.size(); }

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }

  private:
    std::vector<Layer*> m_Layers;
    std::vector<Layer*>::iterator m_LayerInsert;
  };
}

#endif // LAYERSTACK_H