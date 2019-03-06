#ifndef LAYER_H
#define LAYER_H

#include "matrix/src/event/Event.h"

namespace MX {

    class Layer {
    public:
        MX_API Layer(const std::string& name) 
            : m_Name(name) {}
        MX_API virtual ~Layer() {}

        MX_API virtual void attach() {}
        MX_API virtual void detach() {}
        MX_API virtual void update() {}
        MX_API virtual void handleEvent(Event& event) {}

        MX_API inline const std::string getName() { return m_Name; }
    private:
        std::string m_Name;
    };
}

#endif // LAYER_H