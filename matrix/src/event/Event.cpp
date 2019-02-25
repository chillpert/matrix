#include "matrix/src/event/Event.h"
#include "matrix/src/Application.h"
#include <GLFW/glfw3.h>

namespace Matrix {

    void Event::printEventType() const {
        if (event == 0) 
            INFO("Event: Default");
    }

    void Event::handleEvent() {
        switch (m_KeyCode) {
            case GLFW_KEY_ESCAPE:
                Application::get().stop();
            break;
        }
    }
}