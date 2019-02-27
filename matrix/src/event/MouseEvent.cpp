#include "matrix/src/event/MouseEvent.h"
#include "matrix/src/platform/controller/Controller.h"

#define CONTROLLER_MOUSE_MOVED(x,y)       Controller::get().handleMouseMoved(x,y);
#define CONTROLLER_MOUSE_PRESSED(x,y)     Controller::get().handleMousePressed(x,y);
#define CONTROLLER_MOUSE_RELEASED(x,y)    Controller::get().handleMouseReleased(x,y);

namespace Matrix {

    void MouseEvent::handle() {

    }

    void MouseEvent::printEventType() const {
        if (event == 3)
            MX_INFO("Event: DefaultMouse");
    }

    void MouseButtonPressed::handle() {
        CONTROLLER_MOUSE_PRESSED(m_X, m_Y);
    }

    void MouseButtonPressed::printEventType() const {
        if (event == 6)
            MX_INFO("Event: MouseButtonPressed: " + std::to_string(m_KeyCode));
    }

    void MouseButtonReleased::handle() {
        CONTROLLER_MOUSE_RELEASED(m_X, m_Y);
    }

    void MouseButtonReleased::printEventType() const {
        if (event == 7)
            MX_INFO("Event: MouseButtonReleased: " + std::to_string(m_KeyCode));
    }

    void MouseMoved::handle() {
        CONTROLLER_MOUSE_MOVED(m_X, m_Y);
    }

    void MouseMoved::printEventType() const {
        if (event == 8) 
            MX_INFO("Event: MouseMoved: " + std::to_string(m_X) + ", " + std::to_string(m_Y));
    }
}