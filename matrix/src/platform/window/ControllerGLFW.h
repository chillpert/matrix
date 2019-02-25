#ifndef CONTROLLERGLFW_H
#define CONTROLLERGLFW_H

#include "matrix/src/Core.h"

namespace Matrix {
    
    class MATRIX_API ControllerGLFW {
    public:
        ~ControllerGLFW() {}

        static ControllerGLFW get();

        void handleKeyPressed(int keyCode);
        void handleKeyReleased(int keyCode);

        void handleMouseMoved(int x, int y);
    private:
        ControllerGLFW() {}
        // last position of mouse
        int m_X;
        int m_Y;
        // last button pressed
        int m_KeyPressed;
        // last button released
        int m_KeyReleased;
    };
}

#endif // CONTROLLERGLFW_H