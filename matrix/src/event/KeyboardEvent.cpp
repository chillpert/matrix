#include "matrix/src/event/KeyboardEvent.h"
#include "matrix/src/platform/controller/Controller.h"

#define CONTROLLER_KEYBOARD_PRESSED(x)  Controller::get().handleKeyPressed(x);
#define CONTROLLER_KEYBOARD_RELEASED(x) Controller::get().handleKeyReleased(x);

namespace Matrix {

    void KeyboardEvent::handle() {
    
    }

    void KeyboardEvent::printEventType() const {
        if (event == 2)
            MX_INFO("Event: DefaultKeyboard");
    }

    void KeyboardButtonPressed::handle() {
        CONTROLLER_KEYBOARD_PRESSED(m_KeyCode);
    }

    void KeyboardButtonPressed::printEventType() const {
        if (event == 4) 
            MX_INFO("Event: KeyboardButtonPressed: " + std::to_string(m_KeyCode));
    }

    void KeyboardButtonReleased::handle() {
        CONTROLLER_KEYBOARD_RELEASED(m_KeyCode);
    }

    void KeyboardButtonReleased::printEventType() const {
        if (event == 5)
            MX_INFO("Event: KeyboardButtonReleased: " + std::to_string(m_KeyCode));
    }
}