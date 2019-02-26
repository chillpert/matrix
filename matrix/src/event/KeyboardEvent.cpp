#include "matrix/src/event/KeyboardEvent.h"
#include "matrix/src/platform/window/Controller.h"

namespace Matrix {

    void KeyboardEvent::handle() {
    
    }

    void KeyboardEvent::printEventType() const {
        if (event == 2)
            INFO("Event: DefaultKeyboard");
    }

    void KeyboardButtonPressed::handle() {
        Controller::get().handleKeyPressed(m_KeyCode);
    }

    void KeyboardButtonPressed::printEventType() const {
        if (event == 4) 
            INFO("Event: KeyboardButtonPressed: " + std::to_string(m_KeyCode));
    }

    void KeyboardButtonReleased::handle() {
        Controller::get().handleKeyReleased(m_KeyCode);
    }

    void KeyboardButtonReleased::printEventType() const {
        if (event == 5)
            INFO("Event: KeyboardButtonReleased: " + std::to_string(m_KeyCode));
    }
}