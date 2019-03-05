#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "matrix/src/layers/Layer.h"
#include <vector>

namespace MX {

    class LayerStack {
    public:
        LayerStack() {}
        ~LayerStack() {}

        void push(Layer& layer);
        void pop();
        
    private:
        std::vector<Layer*> m_Layers;
    };
}

#endif // LAYERSTACK_H