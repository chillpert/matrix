#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef MX_GLFW_ACTIVE
    #define MX_W_KEY 
    #define MX_A_KEY
    #define MX_S_KEY
    #define MX_D_KEY
    #define MX_C_KEY
    #define MX_SPACE_KEY    GLFW_KEY_SPACE
    #define MX_ESCAPE_KEY   GLFW_KEY_ESCAPE
    #define MX_L_SHIFT_KEY
#elif MX_SDL2_ACTIVE
    #define MX_W_KEY 
    #define MX_A_KEY
    #define MX_S_KEY
    #define MX_D_KEY
    #define MX_C_KEY
    #define MX_SPACE_KEY    SDLK_SPACE
    #define MX_ESCAPE_KEY   SDLK_ESCAPE
    #define MX_L_SHIFT_KEY
#endif

#define PRINT_KEY(x) #x

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