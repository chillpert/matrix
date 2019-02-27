#include "matrix/src/platform/controller/Controller.h"
#include "matrix/src/Application.h"

namespace Matrix {
    
    void Controller::handleKeyPressed(int keyCode) {
        m_KeyPressed = keyCode;
        switch (keyCode) {
            case ESCAPE_KEY:
                Application::get().stop();
                break;
            default:
                MX_WARN("Key " + std::to_string(keyCode) + " is not programmed");
                break;            
        }
    }

    void Controller::handleKeyReleased(int keyCode) {
        m_KeyReleased = keyCode;
        
    }

    void Controller::handleMouseMoved(int x, int y) {
        m_X = x;
        m_Y = y;
    }

    void Controller::handleMousePressed(int x, int y) {

    }

    void Controller::handleMouseReleased(int x, int y) {
        
    }
}