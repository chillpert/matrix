#include "matrix/src/controller/Controller.h"
#include "matrix/src/controller/InputMap.h"
#include "matrix/src/Application.h"

namespace MX {
    
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
                MX_WARN("Key pressed: " + std::to_string(keyCode) + " is not programmed");
                break;            
        }
    }

    void Controller::handleKeyReleased(int keyCode) {
        m_KeyReleased = keyCode;
        switch (keyCode) {
            case MX_ESCAPE_KEY:
                MX_ESCAPE_RELEASED;
                break;
            case MX_SPACE_KEY:
                MX_SPACE_RELEASED;
                break;
            default:
                MX_WARN("Key released: " + std::to_string(keyCode) + " is not programmed");
                break;
        }
    }

    void Controller::handleMouseMoved(int x, int y) {
        m_X = x;
        m_Y = y;
    }

    void Controller::handleMousePressed(int keyCode) {
        switch (keyCode) {
            case MX_LEFT_CLICK:
                MX_LEFT_PRESSED;
                break;
            case MX_RIGHT_CLICK:
                MX_RIGHT_PRESSED;
                break;
            case MX_MIDDLE_CLICK:
                MX_MIDDLE_PRESSED;
                break;
            default:
                MX_WARN("Key pressed: " + std::to_string(keyCode) + " is not programmed");
        }
    }

    void Controller::handleMouseReleased(int keyCode) {
        switch (keyCode) {
            case MX_LEFT_CLICK:
                MX_LEFT_RELEASED;
                break;
            case MX_RIGHT_CLICK:
                MX_RIGHT_RELEASED;
                break;
            case MX_MIDDLE_CLICK:
                MX_RIGHT_RELEASED;
                break;
            default:
                MX_WARN("Key released: " + std::to_string(keyCode) + " is not programmed");
        }
    }

    void Controller::handleMouseScrolled(int x, int y) {
        switch (y) {
            case  1:
                MX_SCROLL_UP;
                break;
            case -1:
                MX_SCROLL_DOWN;
                break;
            default:
                MX_WARN("Scroll direction is not programmed");
                break;
        }
    }
}