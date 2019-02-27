#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef MX_GLFW_ACTIVE
    #define W_KEY 
    #define A_KEY
    #define S_KEY
    #define D_KEY
    #define C_KEY
    #define SPACE_KEY
    #define ESCAPE_KEY GLFW_KEY_ESCAPE
    #define L_SHIFT_KEY
#elif MX_SDL2_ACTIVE
    #define W_KEY 
    #define A_KEY
    #define S_KEY
    #define D_KEY
    #define C_KEY
    #define SPACE_KEY
    #define ESCAPE_KEY SDLK_ESCAPE
    #define L_SHIFT_KEY
#endif

#include "matrix/src/pch/stdafx.h"

namespace Matrix {

    class MATRIX_API Controller {
    public:
        ~Controller() {}
        
        inline static Controller& get() {
            static Controller instance;
            return instance;
        }

        void handleKeyPressed(int keyCode);
        void handleKeyReleased(int keyCode);

        void handleMouseMoved(int x, int y);
        void handleMousePressed(int x, int y);
        void handleMouseReleased(int x, int y);
    protected:
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