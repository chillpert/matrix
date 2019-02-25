#include "matrix/src/event/MouseEvent.h"

#include <string>

namespace Matrix {

    void MouseEvent::printEventType() const {
        if (event == 3)
            INFO("Event: DefaultMouse");
    }

    void MouseButtonPressed::printEventType() const {
        if (event == 6)
            INFO("Event: MouseButtonPressed: " + std::to_string(m_KeyCode));
    }

    void MouseButtonReleased::printEventType() const {
        if (event == 7)
            INFO("Event: MouseButtonReleased: " + std::to_string(m_KeyCode));
    }

    void MouseMoved::printEventType() const {
        if (event == 8) 
            INFO("Event: MouseMoved: " + std::to_string(m_X) + ", " + std::to_string(m_Y));
    }
}