#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "matrix/src/pch/stdafx.h"

namespace Matrix {
    
    class MATRIX_API Controller {
    public:
        ~Controller() {}

        static Controller get();

        void handleKeyPressed(int keyCode);
        void handleKeyReleased(int keyCode);

        void handleMouseMoved(int x, int y);
    private:
        Controller() {}
        // last position of mouse
        int m_X;
        int m_Y;
        // last button pressed
        int m_KeyPressed;
        // last button released
        int m_KeyReleased;
    };
}

#endif // CONTROLLER_H