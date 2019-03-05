#ifndef LAYER_H
#define LAYER_H

#include "matrix/src/event/Event.h"

namespace MX {

    class Layer {
    public:
        Layer(Event& event) 
            : m_Event(event) {}
        ~Layer() {}

        void handleEvent();

        inline std::string getName() { return m_Name; }
    private:
        std::string m_Name;
        Event m_Event;
    };
}

#endif // LAYER_H