#include "matrix/src/platform/window/Controller.h"
#include "matrix/src/Application.h"

#ifdef GLFW_ACTIVE
    #ifdef GLFW_DEFAULT_CONTROLLER
        #define W_KEY 
        #define A_KEY
        #define S_KEY
        #define D_KEY
        #define C_KEY
        #define SPACE_KEY
        #define ESCAPE_KEY Application::get().stop();
        #define L_SHIFT_KEY
    #else
        #define W_KEY 
        #define A_KEY
        #define S_KEY
        #define D_KEY
        #define C_KEY
        #define SPACE_KEY
        #define ESCAPE_KEY
        #define L_SHIFT_KEY
    #endif
#endif

namespace Matrix {

    Controller Controller::get() {
        static Controller instance;
        return instance;
    }

    void Controller::handleKeyPressed(int keyCode) {
        m_KeyPressed = keyCode;
        switch (keyCode) {
            case GLFW_KEY_ESCAPE:
                ESCAPE_KEY;
                break;
            default:
                WARN(std::to_string(keyCode) + " is not programmed");
                break;            
        }
    }

    void Controller::handleKeyReleased(int keyCode) {
        m_KeyReleased = keyCode;
        switch (keyCode) {
            
        }
    }

    void Controller::handleMouseMoved(int x, int y) {
        m_X = x;
        m_Y = y;
    }
}