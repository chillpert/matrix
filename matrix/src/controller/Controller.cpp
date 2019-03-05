#include "matrix/src/controller/Controller.h"
#include "matrix/src/controller/InputMap.h"
#include "matrix/src/Application.h"

namespace MX {
    
    void Controller::handleKeyPressed(int keyCode) {
        m_KeyPressed = keyCode;
        switch (keyCode) {
            case MX_ESCAPE_KEY:
                MX_ESCAPE_PRESSED; break;
            case MX_SPACE_KEY:
                MX_SPACE_PRESSED; break;
            case MX_W_KEY:
                MX_W_PRESSED; break;
            case MX_A_KEY:
                MX_A_PRESSED; break;
            case MX_S_KEY:
                MX_S_PRESSED; break;
            case MX_D_KEY:
                MX_D_PRESSED; break;
            case MX_C_KEY:
                MX_C_PRESSED; break;
            case MX_L_SHIFT_KEY:
                MX_L_SHIFT_PRESSED; break;
            default:
                MX_WARN("MX: Key pressed: " + std::to_string(keyCode) + " is not programmed"); break;            
        }
    }

    void Controller::handleKeyReleased(int keyCode) {
        m_KeyReleased = keyCode;
        switch (keyCode) {
            case MX_ESCAPE_KEY:
                MX_ESCAPE_RELEASED; break;
            case MX_SPACE_KEY:
                MX_SPACE_RELEASED; break;
            case MX_W_KEY:
                MX_W_RELEASED; break;
            case MX_A_KEY:
                MX_A_RELEASED; break;
            case MX_S_KEY:
                MX_S_RELEASED; break;
            case MX_D_KEY:
                MX_D_RELEASED; break;
            case MX_C_KEY:
                MX_C_RELEASED; break;
            case MX_L_SHIFT_KEY:
                MX_L_SHIFT_RELEASED; break;
            default:
                MX_WARN("MX: Key released: " + std::to_string(keyCode) + " is not programmed"); break;
        }
    }

    void Controller::handleMouseMoved(int x, int y) {
        m_X = x;
        m_Y = y;
    }

    void Controller::handleMousePressed(int keyCode) {
        switch (keyCode) {
            case MX_LEFT_CLICK:
                MX_LEFT_PRESSED; break;
            case MX_RIGHT_CLICK:
                MX_RIGHT_PRESSED; break;
            case MX_MIDDLE_CLICK:
                MX_MIDDLE_PRESSED; break;
            default:
                MX_WARN("MX: Key pressed: " + std::to_string(keyCode) + " is not programmed"); break;
        }
    }

    void Controller::handleMouseReleased(int keyCode) {
        switch (keyCode) {
            case MX_LEFT_CLICK:
                MX_LEFT_RELEASED; break;
            case MX_RIGHT_CLICK:
                MX_RIGHT_RELEASED; break;
            case MX_MIDDLE_CLICK:
                MX_RIGHT_RELEASED; break;
            default:
                MX_WARN("MX: Key released: " + std::to_string(keyCode) + " is not programmed"); break;
        }
    }

    void Controller::handleMouseScrolled(int x, int y) {
        switch (y) {
            case  1:
                MX_SCROLL_UP; break;
            case -1:
                MX_SCROLL_DOWN; break;
            default:
                MX_WARN("MX: Scroll direction is not programmed"); break;
        }
    }

    void Controller::handleCloseWindow() {
        Application::get().stop();
    }

    void Controller::handleResizeWindow(int width, int height) {
        Application::get().getWindow()->m_Props.m_Width = width;
        Application::get().getWindow()->m_Props.m_Height = height;
    }
}