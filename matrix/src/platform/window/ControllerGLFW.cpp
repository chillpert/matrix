#include "matrix/src/platform/window/ControllerGLFW.h"
#include "matrix/src/Application.h"
#include "matrix/src/Logger.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace Matrix {

    ControllerGLFW ControllerGLFW::get() {
        static ControllerGLFW instance;
        return instance;
    }

    void ControllerGLFW::handleKeyPressed(int keyCode) {
        m_KeyPressed = keyCode;
        switch (keyCode) {
            case GLFW_KEY_ESCAPE:
                Application::get().stop();
                break;
            default:
                INFO(std::to_string(keyCode) + " is not programmed");
                break;            
        }
    }

    void ControllerGLFW::handleKeyReleased(int keyCode) {
        m_KeyReleased = keyCode;
        switch (keyCode) {
            
        }
    }

    void ControllerGLFW::handleMouseMoved(int x, int y) {
        m_X = x;
        m_Y = y;
    }
}