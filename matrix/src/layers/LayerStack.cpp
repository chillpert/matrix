#include "matrix/src/layers/LayerStack.h"

namespace MX {

    LayerStack::~LayerStack() {
        for (auto it : m_Layers)
            delete it;
    }

    void LayerStack::push(Layer* layer) {
        m_Layers.emplace_back(layer);
    }   

    void LayerStack::pop(Layer* layer) {
        m_Layers.erase(std::remove(m_Layers.begin(), m_Layers.end(), layer));
    }

    std::string LayerStack::toString() {
        std::string message;
        for (auto it : m_Layers) {
            message.append(it->getName() + " ");
        }
        return message + "\n";
    }
}