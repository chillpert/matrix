#include "matrix/src/controller/Controller.h"
#include "matrix/src/controller/InputMap.h"
#include "matrix/src/Application.h"

namespace Matrix {
    
    void Controller::handleKeyPressed(int keyCode) {
        m_KeyPressed = keyCode;
        switch (keyCode) {
            case MX_ESCAPE_KEY:
                MX_ESCAPE_PRESSED;
                break;
            case MX_SPACE_KEY:
                MX_SPACE_PRESSED;
                break;
            default:
                MX_WARN("Key: " + std::to_string(keyCode) + " is not programmed");
                MX_UNKOWN_PRESSED;
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