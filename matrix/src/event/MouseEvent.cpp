#include "matrix/src/event/MouseEvent.h"
#include "matrix/src/controller/Controller.h"

namespace MX {

    void MouseEvent::handle() {

    }

    void MouseEvent::printEventType() const {
        if (event == 3)
            MX_INFO("Event: DefaultMouse");
    }

    void MouseButtonPressed::handle() {
        Controller::get().handleMousePressed(m_KeyCode);
    }

    void MouseButtonPressed::printEventType() const {
        if (event == 6)
            MX_INFO("Event: MouseButtonPressed: " + std::to_string(m_KeyCode));
    }

    void MouseButtonReleased::handle() {
        Controller::get().handleMouseReleased(m_KeyCode);
    }

    void MouseButtonReleased::printEventType() const {
        if (event == 7)
            MX_INFO("Event: MouseButtonReleased: " + std::to_string(m_KeyCode));
    }

    void MouseMoved::handle() {
        Controller::get().handleMouseMoved(m_X, m_Y);
    }

    void MouseMoved::printEventType() const {
        if (event == 8) 
            MX_INFO("Event: MouseMoved: " + std::to_string(m_X) + ", " + std::to_string(m_Y));
    }

    void MouseScrolled::handle() {
        Controller::get().handleMouseScrolled(m_Xaxis, m_Yaxis);
    }

    void MouseScrolled::printEventType() const {
        Controller::get().handleMouseScrolled(m_Xaxis, m_Yaxis);
        MX_INFO("Event: MouseScrolled: " + std::to_string(m_Xaxis) + ", " + std::to_string(m_Yaxis));
    }
}