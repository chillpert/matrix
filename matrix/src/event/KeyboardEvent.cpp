#include "matrix/src/event/KeyboardEvent.h"
#include "matrix/src/controller/Controller.h"

namespace MX {

    void KeyboardButtonPressed::handle() {
        Controller::get().handleKeyPressed(m_KeyCode);
    }

    void KeyboardButtonReleased::handle() {
        Controller::get().handleKeyReleased(m_KeyCode);
    }
}